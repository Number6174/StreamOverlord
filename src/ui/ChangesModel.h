// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_CHANGESMODEL_H
#define STREAMOVERLORD_CHANGESMODEL_H

#include <QAbstractListModel>
#include <QtQml>
#include <utility>
#include <vector>


class ChangesModel : public QAbstractListModel{
    Q_OBJECT
    // Does not have CMake equivalent yet, use QMLRegistrations.h/.cpp for now
    //QML_ELEMENT

public:
    enum ChangesRoles {
        VersionNumberRole = Qt::UserRole + 1,
        URIRole
    };

    ChangesModel();

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    //[[nodiscard]] QMap<int, QVariant> itemData(const QModelIndex &index) const override;

    [[nodiscard]] Q_INVOKABLE QString getURI(int index) const;

    [[nodiscard]] Q_INVOKABLE QString getURIContents(int index);


private:
    std::vector<std::pair<QString,QString>> m_items;
};


#endif //STREAMOVERLORD_CHANGESMODEL_H
