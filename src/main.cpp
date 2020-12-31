// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QStandardPaths>

#include "ui/QMLRegistrations.h"

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    // This sets up storing a couple settings on Windows in the registry at
    // HKEY_CURRENT_USER\SOFTWARE\Number6174\Stream Overlord
    app.setOrganizationName("Number6174");
    app.setOrganizationDomain("number6174.github.io");
    app.setApplicationName("Stream Overlord");

    // Setup default paths for configuration and log files
    QSettings settings;

    if (!settings.value("LogDirectory").isValid()) {
        QString path = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0];
        path.append("/Stream Overlord/Logs");
        settings.setValue("logDirectory", path);
    }
    if (!settings.value("ConfigDirectory").isValid()) {
        QString path = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0];
        path.append("/Stream Overlord/Configuration");
        settings.setValue("configDirectory", path);
    }

    // Registers custom QML types implemented in C++
    registerQML();

    // Setup and start GUI
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/src/ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
