// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Backend.h"

#include <utility>

#include <QDir>
#include <QSettings>
#include <QStandardPaths>

#include "net/NetworkManager.h"
#include "common/ConfigManager.h"

#include <QDebug>

Backend::Backend(QObject *parent) : QObject(parent), m_twitchTokenManager(&m_network) {
    loadSettings();

    // Wire up Twitch::TokenManager
    connect(&m_network, SIGNAL(newOAuth(QString, QVariantMap)),
            &m_twitchTokenManager, SLOT(newOAuth(QString, QVariantMap)));
    connect(&m_twitchTokenManager, SIGNAL(accessTokenChanged(QString)),
            this, SIGNAL(twitchTokenChanged(QString)));
}
/*
Backend::~Backend() {
    m_network.quit();
    m_network.wait();
}
 */

Q_INVOKABLE QString Backend::convertURLtoPath(const QUrl& url) const {
    return QDir::toNativeSeparators(url.toLocalFile());
}

Q_INVOKABLE void Backend::defaultDirectorySettings() {
    m_configDirectory = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0];
    m_configDirectory.append("/Stream Overlord/Configuration");
    m_logDirectory = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0];
    m_logDirectory.append("/Stream Overlord/Logs");
    saveSettings();
    emit(configDirectoryChanged(m_configDirectory));
    emit(logDirectoryChanged(m_logDirectory));
}


QString Backend::getConfigDirectory() const {
    return m_configDirectory;
}
QString Backend::getLogDirectory() const {
    return m_logDirectory;
}

void Backend::setConfigDirectory(QString newDir) {
    m_configDirectory = std::move(newDir);
    saveSettings();
    emit(configDirectoryChanged(m_configDirectory));
}
void Backend::setLogDirectory(QString newDir) {
    m_logDirectory = std::move(newDir);
    saveSettings();
    emit(logDirectoryChanged(m_logDirectory));
}

void Backend::loadSettings() {
    // Load directories from QSettings, defaulting if not present
    QSettings settings;
    if (!settings.value("ConfigurationDirectory").isValid() || !settings.value("LogDirectory").isValid()) {
        defaultDirectorySettings();
    } else {
        m_configDirectory = settings.value("ConfigurationDirectory").toString();
        m_logDirectory = settings.value("LogDirectory").toString();
    }
}

void Backend::saveSettings() {
    QSettings settings;
    settings.setValue("ConfigurationDirectory", m_configDirectory);
    settings.setValue("LogDirectory", m_logDirectory);
}

QString Backend::getTwitchToken() const {
    return m_twitchTokenManager.getAccessToken();
}

void Backend::setTwitchToken(QString newToken) {
    qDebug() << "Set twitch token to " << newToken;
    m_twitchTokenManager.setAccessToken(newToken);
    emit twitchTokenChanged(newToken);
}

QUrl Backend::getTwitchImplicitOAuthURL() {
    return m_twitchTokenManager.getImplicitOAuthURL();
}

void Backend::readConfiguration() {
    // TokenStorage
    Common::TokenStorage ts;
    Common::loadTokenStorage(ts);
    setTwitchToken(ts.twitchAccessToken);
}
void Backend::writeConfiguration() {
    qDebug() << "backend::writeConfiguration";
    // TokenStorage
    Common::TokenStorage ts;
    ts.twitchAccessToken = getTwitchToken();
    Common::writeTokenStorage(ts);
}


