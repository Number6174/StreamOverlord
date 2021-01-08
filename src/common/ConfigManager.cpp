// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ConfigManager.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

#include <QDebug>

Common::LoadTokenResult Common::loadTokenStorage(Common::TokenStorage &ts) {
    // Determine the file to load using the config directory from QSettings
    QSettings settings;

    auto directory = settings.value("ConfigurationDirectory").toString();
    auto filename = QDir::cleanPath(directory + "/tokens.json");

    qDebug() << "file: " << filename;

    // Create the file
    QFile file(filename);

    // Verify file exists
    if (!file.exists()) {
        qDebug() << "Config file not found: " << filename;
        return LoadTokenResult::FileNotFound;
    }

    // Read the contents
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto contents = file.readAll();
    file.close();

    // Process the contents
    QJsonParseError jsonParseError;
    auto doc = QJsonDocument::fromJson(contents, &jsonParseError);

    if (doc.isEmpty()) {
        qDebug() << "Parse error: " << jsonParseError.errorString();
        return LoadTokenResult::InvalidFormat;
    }

    if (!doc.isObject()) {
        qDebug() << "Parse error: Not a JSON object";
        return LoadTokenResult::InvalidFormat;
    }

    auto obj = doc.object();

    // Load Twitch key
    auto twitch = obj["twitch"];
    if (twitch.isUndefined()) {
        qDebug() << "Twitch token not present";
        return LoadTokenResult::InvalidFormat;
    }
    ts.twitchAccessToken = twitch.toString();


    // Done
    return LoadTokenResult::Success;
}

Common::WriteTokenResult Common::writeTokenStorage(const Common::TokenStorage &ts) {
    // Determine the file to load using the config directory from QSettings
    QSettings settings;

    auto directory = settings.value("ConfigurationDirectory").toString();
    auto filename = QDir::cleanPath(directory + "/tokens.json");

    // Ensure directory exists
    QDir qdir;

    if (!qdir.mkpath(directory)) {
        qDebug() << "Configuration directory does not exist and could not be created";
        return WriteTokenResult::CantCreateDir;
    }

    // Build the JSON
    QJsonObject obj;

    obj["twitch"] = ts.twitchAccessToken;
    qDebug() << "Stored access token as " << ts.twitchAccessToken;

    QJsonDocument jsonDocument;
    jsonDocument.setObject(obj);

    // Write the file
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    if (!file.isWritable()) {
        qDebug() << "Cannot open " << filename << " for writing";
        return WriteTokenResult::NotWritable;
    }

    auto bytes = file.write(jsonDocument.toJson(QJsonDocument::JsonFormat::Indented));

    if (bytes == -1) {
        qDebug() << "Error writing: " << file.errorString();
        return WriteTokenResult::ErrorWriting;
    }

    file.close();

    return Common::WriteTokenResult::Success;
}
