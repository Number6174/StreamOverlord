// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Logging.h"

#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h> // support for basic file logging
#include <spdlog/sinks/rotating_file_sink.h> // support for rotating file logging

#include <QSettings>

#include "VersionInfo.h"

namespace {
    void qtMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
        QByteArray localMsg = msg.toLocal8Bit();
        const char *file = context.file ? context.file : "";
        const char *function = context.function ? context.function : "";
        auto logger = spdlog::get("qt");
        switch (type) {
            case QtDebugMsg:
                logger->debug("({}:{}, {}): {}\n",  file, context.line, function, localMsg.constData());
                break;
            case QtInfoMsg:
                logger->info("({}:{}, {}): {}\n",  file, context.line, function, localMsg.constData());
                break;
            case QtWarningMsg:
                logger->warn("({}:{}, {}): {}\n",  file, context.line, function, localMsg.constData());
                break;
            case QtCriticalMsg:
                logger->critical("({}:{}, {}): {}\n",  file, context.line, function, localMsg.constData());
                break;
            case QtFatalMsg:
                logger->error("({}:{}, {}): {}\n",  file, context.line, function, localMsg.constData());
                break;
        }
    }
}

void Common::setupLogging() {
    // Acquire base directory for logs
    QSettings settings;
    auto logDirectory = settings.value("LogDirectory").toString();

    // Setup spdlog loggers
    try {

        std::vector<spdlog::sink_ptr> sinks;

        // a file rotating sink with 1mB size max and 5 rotated files
        sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logDirectory.toStdString() + "/debug.log",
                                                                                      1024 * 1024 * 1, 5));

        // Only use stdout sink in debug mode
        #ifndef NDEBUG
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        #endif

        auto debug_logger = std::make_shared<spdlog::logger>("debug", begin(sinks), end(sinks));
        spdlog::register_logger(debug_logger);
        debug_logger->set_level(spdlog::level::debug);

        debug_logger->info("Program startup. Version {}", getCurrentVersion().toStdString());

        // For logging QT log events
        auto qt_logger = std::make_shared<spdlog::logger>("qt", begin(sinks), end(sinks));
        spdlog::register_logger(qt_logger);
        qt_logger->set_level(spdlog::level::debug);

        // OAuth events
        auto oauth_logger = std::make_shared<spdlog::logger>("oauth", begin(sinks), end(sinks));
        spdlog::register_logger(oauth_logger);
        oauth_logger->set_level(spdlog::level::debug);

        // Config events
        auto config_logger = std::make_shared<spdlog::logger>("config", begin(sinks), end(sinks));
        spdlog::register_logger(config_logger);
        config_logger->set_level(spdlog::level::debug);

        // Twitch events
        auto twitch_logger = std::make_shared<spdlog::logger>("twitch", begin(sinks), end(sinks));
        spdlog::register_logger(twitch_logger);
        twitch_logger->set_level(spdlog::level::debug);

    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }

    // Redirect QT logs to use our logs
    qInstallMessageHandler(qtMessageOutput);
}

void Common::logShutdown() {
    auto logger = spdlog::get("debug");
    logger->info("Program shutdown");
}
