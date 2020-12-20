// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_EVENTMODEL_H
#define STREAMOVERLORD_EVENTMODEL_H

#include <QAbstractListModel>
#include <QtQml>
#include <vector>

#include "Event.h"

class EventModel : public QAbstractListModel {
    Q_OBJECT
    // Does not have CMake equivalent yet, use QMLRegistrations.h/.cpp for now
    //QML_ELEMENT

public:

    enum EventRoles {
        TimeRole = Qt::UserRole + 1,
        SourceRole
    };
    EventModel();

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

private:
    std::vector<Event> m_items;
};


#endif //STREAMOVERLORD_EVENTMODEL_H
