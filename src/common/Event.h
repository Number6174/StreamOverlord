// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_EVENT_H
#define STREAMOVERLORD_EVENT_H

#include <QString>

class Event {
public:
    Event(QString time, QString source);

    [[nodiscard]] const QString &getTime() const;

    [[nodiscard]] const QString &getSource() const;
private:
    // FIXME: These really shouldn't be QString, but used just to
    // make something work
    QString m_time;
    QString m_source;

};


#endif //STREAMOVERLORD_EVENT_H
