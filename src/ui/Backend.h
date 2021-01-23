// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_BACKEND_H
#define STREAMOVERLORD_BACKEND_H

#include <QObject>
#include <QUrl>
#include <QThread>

#include "twitch/TokenManager.h"
#include "net/NetworkManager.h"


class Backend : public QObject{
    // Register with QT
    Q_OBJECT
    Q_PROPERTY(QString configDirectory READ getConfigDirectory WRITE setConfigDirectory NOTIFY configDirectoryChanged)
    Q_PROPERTY(QString logDirectory READ getLogDirectory WRITE setLogDirectory NOTIFY logDirectoryChanged)
    Q_PROPERTY(QString twitchToken READ getTwitchToken WRITE setTwitchToken NOTIFY twitchTokenChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    //~Backend() override;
    // Note QObjects are not copyable or assignable, so this is not a rule of 5 violation

    Q_INVOKABLE [[nodiscard]] QString convertURLtoPath(const QUrl& url) const;
    Q_INVOKABLE void defaultDirectorySettings();
    [[nodiscard]] QString getLogDirectory() const;
    [[nodiscard]] QString getConfigDirectory() const;
    [[nodiscard]] QString getTwitchToken() const;
    Q_INVOKABLE QUrl getTwitchImplicitOAuthURL();
    Q_INVOKABLE void readConfiguration();
    Q_INVOKABLE void writeConfiguration();
    Q_INVOKABLE [[nodiscard]] QString getCurrentVersion() const;

    static QString getDefaultLogDirectory();
    static QString getDefaultConfigDirectory();

signals:
    void logDirectoryChanged(QString newDir);
    void configDirectoryChanged(QString newDir);
    void twitchTokenChanged(QString newToken);
    void warningDialog(QString message);

public slots:
    void setLogDirectory(QString newDir);
    void setConfigDirectory(QString newDir);
    void setTwitchToken(QString newToken);
    void handleOAuthError(QString message);

private:

    void loadSettings();
    void saveSettings();
    QString m_logDirectory;
    QString m_configDirectory;
    Twitch::TokenManager m_twitchTokenManager;

    NetworkManager m_network;
};


#endif //STREAMOVERLORD_BACKEND_H
