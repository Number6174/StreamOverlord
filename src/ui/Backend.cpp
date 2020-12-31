// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Backend.h"

#include <utility>

#include <QDir>
#include <QSettings>
#include <QStandardPaths>

Backend::Backend(QObject *parent) : QObject(parent) {
    loadSettings();
    //connect(this, &Backend::logDirectoryChanged, this, &Backend::setLogDirectory);
}

Q_INVOKABLE QString Backend::convertURLtoPath(QUrl url) const {
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
