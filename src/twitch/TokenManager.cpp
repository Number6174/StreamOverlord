// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TokenManager.h"

#include <QString>
#include <QDir>
#include <QUrl>
#include <QUrlQuery>


#include <QDebug>
#include <utility>

#include "common/NonceGenerator.h"

namespace Twitch {
    TokenManager::TokenManager(NetworkManager *n, QObject *parent) : QObject(parent), netman(n) {
    }

    QUrl TokenManager::getImplicitOAuthURL() const {
        // Construct URL
        QUrl authUri("https://id.twitch.tv/oauth2/authorize");

        QUrlQuery params;
        params.addQueryItem("client_id", "snm2rhq703dbcp9lqc2sbl30tcqp80");
        params.addQueryItem("redirect_uri", "http://localhost:6174/twitchoauth");
        params.addQueryItem("response_type", "token");
        params.addQueryItem("scope", "chat:read");

        state = QString{common::generateOAuthState().c_str()};
        params.addQueryItem("state", state);

        authUri.setQuery(params);

        return authUri;
    }

    const QString &TokenManager::getAccessToken() const {
        return access_token;
    }

    void TokenManager::setAccessToken(const QString &accessToken) {
        access_token = accessToken;
    }

    const QVector<Scope> & TokenManager::getScope() const {
        return scope;
    }

    void TokenManager::newOAuth(QString path, QVariantMap receivedData) {
        // Verify it is for us
        if (path != "/twitchoauthajax")
            return;

        // Ensure the state matches
        if (state != receivedData["state"]) {
            // Something went wrong
            qDebug() << "Received OAuth response but state didn't match";
            //return;
        }

        access_token = receivedData["access_token"].toString();
        emit accessTokenChanged(access_token);
        //qDebug() << "Here";
    }

    void TokenManager::revalidateAuthToken() {

    }


}