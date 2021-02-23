// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_CONFIGMANAGER_H
#define STREAMOVERLORD_CONFIGMANAGER_H

#include <QJsonDocument>
#include <QString>

namespace Common {
    struct TokenStorage {
        QString twitchAccessToken;
    };

    enum class LoadTokenResult {
        Success,
        FileNotFound,
        InvalidFormat
    };
    LoadTokenResult loadTokenStorage(TokenStorage &ts);
    LoadTokenResult processTokenJSON(const QJsonDocument &contents, TokenStorage &ts);

    enum class WriteTokenResult {
        Success,
        CantCreateDir,
        NotWritable,
        ErrorWriting
    };
    WriteTokenResult writeTokenStorage(const TokenStorage &ts);

}

#endif //STREAMOVERLORD_CONFIGMANAGER_H
