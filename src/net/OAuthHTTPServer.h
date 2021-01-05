// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_OAUTHHTTPSERVER_H
#define STREAMOVERLORD_OAUTHHTTPSERVER_H

#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QUrl>

// Significant portions of this class are based upon QOAuthHttpServerReplyHandler
// from QT's networkauth module licensed under GPL3+

// This version changes some things around to support multiple OAuth sources
// within one program by looking at the URL used, and also work better
// within an implicit OAuth2 flow (which networkauth does not support)

// The substantial portion modified is what was originally
// QOAuthHttpServerReplyHandlerPrivate::_q_answerClient
// which is now just answerClient
// Since that is part of the Private implementation, the class was rebuilt it instead of
// something more sensible like subclassing and overriding.

// In particular Twitch's implicit OAuth sends its response as:
// https://<your registered redirect URI>#access_token=<an access token>
// And the browser doesn't pass along the URI fragment. As a hack, if there are no
// URI query parameters, the response includes some Javascript that takes the fragment
// and converts it to a query

// Once this program is ported to QT6, investigate replacing this class with
// qt-extensions/qthttpserver


class OAuthHTTPServer : public QObject{
    Q_OBJECT

public:
    explicit OAuthHTTPServer(QObject *parent = nullptr);
    ~OAuthHTTPServer() override;

signals:
    void newOAuth(QString path, QVariantMap receivedData);

private slots:
    void newConnection();

private:
    void readyRead(QTcpSocket *socket);
    void answerClient(QTcpSocket *socket, const QUrl &url);

    void answerClient200(QTcpSocket *socket, const QByteArray &message);
    void answerClient404(QTcpSocket *socket);
    void answerClientTwitchFragmentToQuery(QTcpSocket *socket);
    void answerClientTwitchAJAX(QTcpSocket *socket);

    void emitQuery(const QUrl &url);

    QTcpServer httpServer;

    struct QHttpRequest {
        quint16 port = 0;

        bool readMethod(QTcpSocket *socket);
        bool readUrl(QTcpSocket *socket);
        bool readStatus(QTcpSocket *socket);
        bool readHeader(QTcpSocket *socket);

        enum class State {
            ReadingMethod,
            ReadingUrl,
            ReadingStatus,
            ReadingHeader,
            ReadingBody,
            AllDone
        } state = State::ReadingMethod;
        QByteArray fragment;

        enum class Method {
            Unknown,
            Head,
            Get,
            Put,
            Post,
            Delete,
        } method = Method::Unknown;
        QUrl url;
        QPair<quint8, quint8> version;
        QMap<QByteArray, QByteArray> headers;
    };
    QMap<QTcpSocket *, QHttpRequest> clients;
};


#endif //STREAMOVERLORD_OAUTHHTTPSERVER_H
