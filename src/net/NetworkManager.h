// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_NETWORKMANAGER_H
#define STREAMOVERLORD_NETWORKMANAGER_H

#include <QObject>

// Forward declare is good enough here
class OAuthHTTPServer;

class NetworkManager : public QObject {
    Q_OBJECT;
public:
    explicit NetworkManager(QObject *parent = nullptr);

private:
    OAuthHTTPServer *oAuthServer;
};


#endif //STREAMOVERLORD_NETWORKMANAGER_H
