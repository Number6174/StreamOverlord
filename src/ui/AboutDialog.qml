// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Dialog {
    id: root
    title: "About Stream Overlord"
    ColumnLayout {
        Text {
            text: "Stream Overlord 0.0.1"
        }
        Text {
            text: "Copyright 2020-2021 Number6174"
        }

    }

    standardButtons: StandardButton.Close
}
