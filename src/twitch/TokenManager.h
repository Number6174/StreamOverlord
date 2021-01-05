// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_TOKENMANAGER_H
#define STREAMOVERLORD_TOKENMANAGER_H

#include <QObject>
#include <QUrl>
#include <QVariant>

#include "OAuthScopes.h"
#include "net/NetworkManager.h"

namespace Twitch {

    class TokenManager : public QObject {
    Q_OBJECT
    public:
        explicit TokenManager(NetworkManager *netman, QObject *parent = nullptr);

        QUrl getImplicitOAuthURL() const;

        const QString &getAccessToken() const;
        void setAccessToken(const QString &accessToken);
        const QVector<Scope> & getScope() const;

    public slots:
        void newOAuth(QString path, QVariantMap receivedData);
        void revalidateAuthToken();

    signals:
        void accessTokenChanged(QString newToken);

    private:
        mutable QString state;
        QString access_token;
        QVector<Scope> scope;
        NetworkManager *netman;

    };
}


#endif //STREAMOVERLORD_TOKENMANAGER_H
