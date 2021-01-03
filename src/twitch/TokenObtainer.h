// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_TOKENOBTAINER_H
#define STREAMOVERLORD_TOKENOBTAINER_H

#include <memory>

#include <QNetworkReply>
#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>

namespace Twitch {

    // This class shouldn't need to exist, but in QOAuthHTTPServerReplyHandler
    // the callback function is basically hard coded to return an address of the
    // form http://127.0.0.1:port. However Twitch only permits use of http
    // (no TLS) for return_uri if it is of the form http://localhost:port
    //
    // The RFC, notably https://tools.ietf.org/html/rfc8252#section-8.3 says
    // that localhost is not recommended.
    //
    // but Twitch only permits http for return_uri of
    // the form http://localhost:port
    /*
    class TwitchOAuthHttpServerReplyHandler : public QOAuthHttpServerReplyHandler {
    public:
        explicit TwitchOAuthHttpServerReplyHandler(quint16 port, QObject *parent = nullptr);
        QString callback() const override;
    };
*/

    class TokenObtainer : public QObject {
    Q_OBJECT
    public:
        TokenObtainer(QObject *parent = nullptr);

        //virtual ~TokenObtainer();




    public slots:
        void authenticate();
        void receivedReply(const QVariantMap &values);

    signals:
        void gotToken(const QString &token);

    private:
        std::unique_ptr<QOAuth2AuthorizationCodeFlow> flow;
        std::unique_ptr<QOAuthHttpServerReplyHandler> replyHandler;
        QString stateNonce;
    };
}


#endif //STREAMOVERLORD_TOKENOBTAINER_H
