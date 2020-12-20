// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Event.h"

#include <utility>

Event::Event(QString time, QString source) : m_time(std::move(time)), m_source(std::move(source)){

}

const QString &Event::getTime() const {
    return m_time;
}

const QString &Event::getSource() const {
    return m_source;
}
