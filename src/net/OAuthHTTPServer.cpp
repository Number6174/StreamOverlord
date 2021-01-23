// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "OAuthHTTPServer.h"

#include <QString>
#include <QtNetwork>

#include <QDebug>

OAuthHTTPServer::OAuthHTTPServer(QObject *parent) : QObject(parent), httpServer(this) {
    logger = spdlog::get("oauth");
    // Only accept connections from LocalHost port 6174
    if (!httpServer.listen(QHostAddress::LocalHost, 6174)) {
        logger->critical("Unable to start the OAuth server: {}.", httpServer.errorString().toStdString());
        return;
    }

    // Wire it up
    connect(&httpServer, &QTcpServer::newConnection, this, &OAuthHTTPServer::newConnection);
}

OAuthHTTPServer::~OAuthHTTPServer() {
    if (httpServer.isListening())
        httpServer.close();
}

void OAuthHTTPServer::newConnection() {
    // Accept the connection
    QTcpSocket *socket = httpServer.nextPendingConnection();

    QObject::connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    QObject::connect(socket, &QTcpSocket::readyRead, [this, socket]() { readyRead(socket); });
}

void OAuthHTTPServer::readyRead(QTcpSocket *socket) {
    if (!clients.contains(socket))
        clients[socket].port = httpServer.serverPort();

    QHttpRequest *request = &clients[socket];
    bool error = false;

    if (Q_LIKELY(request->state == QHttpRequest::State::ReadingMethod))
        if (Q_UNLIKELY(error = !request->readMethod(socket)))
            logger->warn("Invalid Method");

    if (Q_LIKELY(!error && request->state == QHttpRequest::State::ReadingUrl))
        if (Q_UNLIKELY(error = !request->readUrl(socket)))
            logger->warn("Invalid URL");

    if (Q_LIKELY(!error && request->state == QHttpRequest::State::ReadingStatus))
        if (Q_UNLIKELY(error = !request->readStatus(socket)))
            logger->warn("Invalid Status");

    if (Q_LIKELY(!error && request->state == QHttpRequest::State::ReadingHeader))
        if (Q_UNLIKELY(error = !request->readHeader(socket)))
            logger->warn("Invalid Header");

    if (error) {
        socket->disconnectFromHost();
        clients.remove(socket);
    } else if (!request->url.isEmpty()) {
        Q_ASSERT(request->state != QHttpRequest::State::ReadingUrl);
        answerClient(socket, request->url);
        clients.remove(socket);
    }
}

void OAuthHTTPServer::answerClient(QTcpSocket *socket, const QUrl &url) {
    logger->info("Request {}", url.path().toStdString());
    if (url.path() == "/twitchoauth") {
        if (!url.hasQuery()) {
            // What we want is currently a fragment in the URL
            logger->info("Sending Twitch AJAX callback");
            answerClientTwitchFragmentToQuery(socket);
        } else {
            // An error occurred
            logger->warn("Received OAuth error from Twitch");

            const QUrlQuery query(url.query());
            const auto items = query.queryItems();
            logger->debug("Received in URL Query:");
            for (const auto &item : items)
                logger->debug("{}: {}", item.first.toStdString(), item.second.toStdString());

            answerClientTwitchError(socket);
            emit failedOAuth("Twitch");
        }
    } else if (url.path() == "/twitchoauthajax") {
        // Received fragment as AJAX request
        // Process query
        logger->info("Received Twitch AJAX callback");
        answerClientTwitchAJAX(socket);
        emitQuery(url);
    } else {
        // Unknown path(), return 404
        logger->info("Sending 404");
        answerClient404(socket);
    }
}

void OAuthHTTPServer::answerClient200(QTcpSocket *socket, const QByteArray &message) {
    const QByteArray htmlSize = QByteArray::number(message.size());
    const QByteArray replyMessage = QByteArrayLiteral("HTTP/1.0 200 OK \r\n"
                                                      "Content-Type: text/html; "
                                                      "charset=\"utf-8\"\r\n"
                                                      "Content-Length: ") + htmlSize +
                                    QByteArrayLiteral("\r\n\r\n") +
                                    message;

    socket->write(replyMessage);
    socket->disconnectFromHost();
}

void OAuthHTTPServer::answerClient404(QTcpSocket *socket) {
    const QByteArray replyMessage = QByteArrayLiteral("HTTP/2 404\r\n"
                                                      "content-type: text/html; charset=UTF-8\r\n"
                                                      "content-length: 0\r\n\r\n");
    socket->write(replyMessage);
    socket->disconnectFromHost();
}

void OAuthHTTPServer::answerClientTwitchFragmentToQuery(QTcpSocket *socket) {
    const QByteArray message =
            QByteArrayLiteral("<html><head><title>")
            + qApp->applicationName().toUtf8()
            + QByteArrayLiteral("</title></head><body>"
                                "Response <div id=\"response\">pending.</div>"
                                "<script>"
                                "var xhttp = new XMLHttpRequest();"
                                "xhttp.onreadystatechange = function () {"
                                "if (this.readyState == 4 && this.status == 200) {"
                                "document.getElementById(\"response\").innerHTML = this.responseText;"
                                "}};"
                                "xhttp.open(\"GET\", window.location.pathname + \"ajax?\" + window.location.hash.substring(1), true);"
                                "xhttp.send();"
                                "</script>"
                                "<noscript>Javascript must be enabled for this to work.</noscript>"
                                "</body></html>");

    answerClient200(socket, message);
}

void OAuthHTTPServer::answerClientTwitchAJAX(QTcpSocket *socket) {
    const QByteArray message = QByteArrayLiteral("is complete. You may now close this window.");
    answerClient200(socket, message);
}

void OAuthHTTPServer::answerClientTwitchError(QTcpSocket *socket) {
    const QByteArray message =
            QByteArrayLiteral("<html><head><title>")
            + qApp->applicationName().toUtf8()
            + QByteArrayLiteral("</title></head><body>"
                                "OAuth failed. Please attempt to re-obtain a token."
                                "</body></html>");

    answerClient200(socket, message);
}

void OAuthHTTPServer::emitQuery(const QUrl &url) {
    // Convert the query components to a map and emit
    QVariantMap receivedData;
    const QUrlQuery query(url.query());
    const auto items = query.queryItems();
    for (const auto &item : items)
        receivedData.insert(item.first, item.second);

    emit newOAuth(url.path(), receivedData);
}

bool OAuthHTTPServer::QHttpRequest::readMethod(QTcpSocket *socket) {
    bool finished = false;
    while (socket->bytesAvailable() && !finished) {
        char c;
        socket->getChar(&c);
        if (std::isupper(c) && fragment.size() < 6)
            fragment += c;
        else
            finished = true;
    }
    if (finished) {
        if (fragment == "HEAD")
            method = Method::Head;
        else if (fragment == "GET")
            method = Method::Get;
        else if (fragment == "PUT")
            method = Method::Put;
        else if (fragment == "POST")
            method = Method::Post;
        else if (fragment == "DELETE")
            method = Method::Delete;
        else
            qDebug("Invalid operation %s", fragment.data());

        state = State::ReadingUrl;
        fragment.clear();

        return method != Method::Unknown;
    }
    return true;
}

bool OAuthHTTPServer::QHttpRequest::readUrl(QTcpSocket *socket) {
    bool finished = false;
    while (socket->bytesAvailable() && !finished) {
        char c;
        socket->getChar(&c);
        if (std::isspace(c))
            finished = true;
        else
            fragment += c;
    }
    if (finished) {
        if (!fragment.startsWith("/")) {
            qDebug("Invalid URL path %s", fragment.constData());
            return false;
        }
        url.setUrl(QStringLiteral("http://127.0.0.1:") + QString::number(port) +
                   QString::fromUtf8(fragment));
        state = State::ReadingStatus;
        if (!url.isValid()) {
            qDebug("Invalid URL %s", fragment.constData());
            return false;
        }
        fragment.clear();
        return true;
    }
    return true;
}

bool OAuthHTTPServer::QHttpRequest::readStatus(QTcpSocket *socket) {
    bool finished = false;
    while (socket->bytesAvailable() && !finished) {
        char c;
        socket->getChar(&c);
        fragment += c;
        if (fragment.endsWith("\r\n")) {
            finished = true;
            fragment.resize(fragment.size() - 2);
        }
    }
    if (finished) {
        if (!std::isdigit(fragment.at(fragment.size() - 3)) ||
            !std::isdigit(fragment.at(fragment.size() - 1))) {
            qDebug("Invalid version");
            return false;
        }
        version = qMakePair(fragment.at(fragment.size() - 3) - '0',
                            fragment.at(fragment.size() - 1) - '0');
        state = State::ReadingHeader;
        fragment.clear();
    }
    return true;
}

bool OAuthHTTPServer::QHttpRequest::readHeader(QTcpSocket *socket) {
    while (socket->bytesAvailable()) {
        char c;
        socket->getChar(&c);
        fragment += c;
        if (fragment.endsWith("\r\n")) {
            if (fragment == "\r\n") {
                state = State::ReadingBody;
                fragment.clear();
                return true;
            } else {
                fragment.chop(2);
                const int index = fragment.indexOf(':');
                if (index == -1)
                    return false;

                const QByteArray key = fragment.mid(0, index).trimmed();
                const QByteArray value = fragment.mid(index + 1).trimmed();
                headers.insert(key, value);
                fragment.clear();
            }
        }
    }
    return false;
}
