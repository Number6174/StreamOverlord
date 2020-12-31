// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_BACKEND_H
#define STREAMOVERLORD_BACKEND_H

#include <QObject>
#include <QUrl>

class Backend : public QObject{
    // Register with QT
    Q_OBJECT
    Q_PROPERTY(QString configDirectory READ getConfigDirectory WRITE setConfigDirectory NOTIFY configDirectoryChanged)
    Q_PROPERTY(QString logDirectory READ getLogDirectory WRITE setLogDirectory NOTIFY logDirectoryChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE [[nodiscard]] QString convertURLtoPath(const QUrl& url) const;
    Q_INVOKABLE void defaultDirectorySettings();
    [[nodiscard]] QString getLogDirectory() const;
    [[nodiscard]] QString getConfigDirectory() const;

signals:
    void logDirectoryChanged(QString newDir);
    void configDirectoryChanged(QString newDir);

public slots:
    void setLogDirectory(QString newDir);
    void setConfigDirectory(QString newDir);

private:

    void loadSettings();
    void saveSettings();
    QString m_logDirectory;
    QString m_configDirectory;

};


#endif //STREAMOVERLORD_BACKEND_H
