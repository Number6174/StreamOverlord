// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "EventModel.h"

#include <iostream>

int EventModel::rowCount(const QModelIndex &parent) const {
    return static_cast<int>(m_items.size());
}

QVariant EventModel::data(const QModelIndex &index, int role) const {
    // Invalid index
    if (!index.isValid() || index.row() >= m_items.size())
        return QVariant();

    const auto &item = m_items[index.row()];

    if (role == EventRoles::TimeRole)
        return item.getTime();
    if (role == EventRoles::SourceRole)
        return item.getSource();
    if (role == Qt::ToolTipRole)
        return QString("Tooltip");

    // All else failed
    return QVariant();
}

QVariant EventModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QStringLiteral("Column %1").arg(section);
    else
        return QStringLiteral("Row %1").arg(section);
}

EventModel::EventModel() {
    for (int i = 0; i < 10000; ++i) {
        std::string time = "Time" + std::to_string(i);
        std::string source = "Source" + std::to_string(i);
        m_items.emplace_back(Event(time.c_str(), source.c_str()));
    }
}

QHash<int, QByteArray> EventModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[EventRoles::TimeRole] = "time";
    roles[EventRoles::SourceRole] = "source";
    roles[Qt::ToolTipRole] = "tooltip";
    return roles;
}
