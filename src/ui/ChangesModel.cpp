// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ChangesModel.h"

#include <QDirIterator>
#include <QVersionNumber>

#include <algorithm>
#include <string>

ChangesModel::ChangesModel() {
    QDirIterator it(":/dist");
    auto prefixLength = std::string{":/dist/changes-"}.length();
    auto suffixLength = std::string{".md"}.length();
    while (it.hasNext()) {
        auto path = it.next();
        auto version = path.mid(prefixLength, static_cast<int>(path.length()) - prefixLength - suffixLength);
        m_items.emplace_back(QString(version.data()), path);
    }

    std::sort(m_items.begin(), m_items.end(),
              [](const auto &a, const auto &b) {
                  return QVersionNumber::fromString(a.first) > QVersionNumber::fromString(b.first);
              });
}

[[nodiscard]] int ChangesModel::rowCount(const QModelIndex &parent) const {
    return static_cast<int>(m_items.size());
}

QHash<int, QByteArray> ChangesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ChangesRoles::VersionNumberRole] = "versionNumber";
    roles[ChangesRoles::URIRole] = "uri";
    return roles;
}

QVariant ChangesModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QStringLiteral("Column %1").arg(section);
    else
        return QStringLiteral("Row %1").arg(section);
}

QVariant ChangesModel::data(const QModelIndex &index, int role) const {
    // Invalid index
    if (!index.isValid() || index.row() >= m_items.size())
        return QVariant();

    const auto &item = m_items[index.row()];

    if (role == ChangesRoles::VersionNumberRole)
        return item.first;
    if (role == ChangesRoles::URIRole)
        return item.second;

    // All else failed
    return QVariant();
}

QString ChangesModel::getURI(int index) const {
    // Invalid index
    if (index >= m_items.size())
        return QString();

    return m_items[index].second;
}

QString ChangesModel::getURIContents(int index) {
    // Invalid index
    if (index >= m_items.size())
        return QString();

    QFile file(m_items[index].second);
    file.open(QIODevice::ReadOnly);
    auto result = QString(file.readAll());
    file.close();

    return result;
}

