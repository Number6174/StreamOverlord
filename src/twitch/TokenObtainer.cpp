// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TokenObtainer.h"

#include <QString>
#include <QDir>
#include <QUrl>
#include <QUrlQuery>

#include <QDesktopServices>

#include <QDebug>

#include "common/NonceGenerator.h"

namespace Twitch {
/*
    TwitchOAuthHttpServerReplyHandler::TwitchOAuthHttpServerReplyHandler(quint16 port, QObject *parent) :
            QOAuthHttpServerReplyHandler(port, parent) {}

    QString TwitchOAuthHttpServerReplyHandler::callback() const {
        return redirectUri.toString(QUrl::EncodeDelimiters);
    }
*/

    TokenObtainer::TokenObtainer(QObject *parent) : QObject(parent) {


/*
        flow = std::make_unique<QOAuth2AuthorizationCodeFlow>(this);
        //this->flow = new QOAuth2AuthorizationCodeFlow(this);
        flow->setScope("chat:read");
        connect(flow.get(), &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);

        //const QUrl authUri("https://id.twitch.tv/oauth2/authorize");
        //const auto clientId = "snm2rhq703dbcp9lqc2sbl30tcqp80";
        //const QUrl tokenUri("https://id.twitch.tv/oauth2/.well-known/openid-configuration");
        //const auto clientSecret("YOUR-CLIENT-SECRET");
        //const QUrl redirectUri("http://localhost:6174/twitchoath");
        const auto port = static_cast<quint16>(redirectUri.port());
        flow->setAuthorizationUrl(authUri);
        flow->setClientIdentifier(clientId);
        flow->setAccessTokenUrl(tokenUri);
        //flow->setClientIdentifierSharedKey(clientSecret);


        flow->setModifyParametersFunction([](QAbstractOAuth::Stage stage, QVariantMap *parameters) {
            // Percent-decode the "code" parameter so Google can match it
            if (stage == QAbstractOAuth::Stage::RequestingAccessToken) {
                //QByteArray code = parameters->value("code").toByteArray();
                //(*parameters)["code"] = QUrl::fromPercentEncoding(code);
                QByteArray code = parameters->value("redirect_uri").toByteArray();
                (*parameters)["redirect_uri"] = QUrl::fromPercentEncoding(code);

                for (const auto &pair : parameters->toStdMap()) {
                    qDebug() << pair.first << ":" << pair.second.toString();
                }
            }
        });


        qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();




        //QOAuthHttpServerReplyHandler *replyHandler = new QOAuthHttpServerReplyHandler(port, this);
        replyHandler = std::make_unique<TwitchOAuthHttpServerReplyHandler>(port, this);
        //replyHandler->setProperty("redirect_uri", redirectUri);

        flow->setReplyHandler(replyHandler.get());

        connect(flow.get(), &QOAuth2AuthorizationCodeFlow::granted, [=]() {
            const QString token = flow->token();
            emit gotToken(token);
        });
        */
    }

    /*TokenObtainer::~TokenObtainer() {
        delete this->flow;
    }*/

    void TokenObtainer::authenticate() {

        //const QUrl redirectUri("http://localhost:6174/twitchoath");
        //const auto port = static_cast<quint16>(redirectUri.port());

        // Startup reply handler
        replyHandler = std::make_unique<QOAuthHttpServerReplyHandler>(6174, this);
        connect(replyHandler.get(), &QOAuthHttpServerReplyHandler::callbackReceived, this, &TokenObtainer::receivedReply);

        // Construct URL
        QUrl authUri("https://id.twitch.tv/oauth2/authorize");

        QUrlQuery params;
        params.addQueryItem("client_id", "snm2rhq703dbcp9lqc2sbl30tcqp80");
        params.addQueryItem("redirect_uri", "http://localhost:6174/twitchoauth");
        params.addQueryItem("response_type", "token");
        params.addQueryItem("scope", "chat:read");

        stateNonce = QString{common::generateOAuthState().c_str()};
        params.addQueryItem("state", stateNonce);

        authUri.setQuery(params);
        //const QUrl tokenUri("https://id.twitch.tv/oauth2/.well-known/openid-configuration");
        //const QUrl tokenUri("https://id.twitch.tv/oauth2/token");
        //const auto clientSecret("YOUR-CLIENT-SECRET");

        qDebug() << authUri;

        QDesktopServices::openUrl(authUri);

        //flow->grant();
    }

    void TokenObtainer::receivedReply(const QVariantMap &values) {


        // Process data
        qDebug() << "received reply:";
        for (const auto &pair: values.toStdMap()) {
            qDebug() << pair.first << ": " << pair.second;
        }

        // Shutdown reply handler
        //replyHandler.reset(nullptr);
    }


}