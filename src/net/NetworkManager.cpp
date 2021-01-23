// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "NetworkManager.h"

#include "net/OAuthHTTPServer.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent),
                                                  oAuthServer(new OAuthHTTPServer(this)) {
    // Signal to Signal
    connect(oAuthServer, SIGNAL(newOAuth(QString, QVariantMap)),
            this, SIGNAL(newOAuth(QString, QVariantMap)));
    connect(oAuthServer, SIGNAL(failedOAuth(QString)),
            this, SIGNAL(failedOAuth(QString)));
}
