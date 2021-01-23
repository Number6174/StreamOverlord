// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Backend.h"

#include <utility>

#include <QDir>
#include <QSettings>
#include <QStandardPaths>

#include "common/ConfigManager.h"
#include "common/VersionInfo.h"

Backend::Backend(QObject *parent) : QObject(parent), m_twitchTokenManager(&m_network) {
    loadSettings();

    readConfiguration();

    // Wire up Twitch::TokenManager
    connect(&m_network, SIGNAL(newOAuth(QString, QVariantMap)),
            &m_twitchTokenManager, SLOT(newOAuth(QString, QVariantMap)));
    connect(&m_twitchTokenManager, SIGNAL(accessTokenChanged(QString)),
            this, SIGNAL(twitchTokenChanged(QString)));
    connect(&m_network, SIGNAL(failedOAuth(QString)),
            this, SLOT(handleOAuthError(QString)));
}

Q_INVOKABLE QString Backend::convertURLtoPath(const QUrl& url) const {
    return QDir::toNativeSeparators(url.toLocalFile());
}

Q_INVOKABLE void Backend::defaultDirectorySettings() {
    m_configDirectory = getDefaultConfigDirectory();
    m_logDirectory = getDefaultLogDirectory();
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
    // Load directories from QSettings
    QSettings settings;
    m_configDirectory = settings.value("ConfigurationDirectory").toString();
    m_logDirectory = settings.value("LogDirectory").toString();
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
    m_twitchTokenManager.setAccessToken(newToken);
    emit twitchTokenChanged(newToken);
}

void Backend::handleOAuthError(QString message) {
    emit warningDialog("An error occurred while obtaining an OAuth token from "
                       + message + ". Please re-obtain.");
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
    // TokenStorage
    Common::TokenStorage ts;
    ts.twitchAccessToken = getTwitchToken();
    Common::writeTokenStorage(ts);
}

QString Backend::getCurrentVersion() const {
    return Common::getCurrentVersion();
}

QString Backend::getDefaultLogDirectory() {
    return QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0].append("/Stream Overlord/Logs");
}

QString Backend::getDefaultConfigDirectory() {
    return QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0].append(
            "/Stream Overlord/Configuration");
}
