// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import StreamOverlord 1.0

Dialog {
    id: root
    title: "Warning"

    property alias text: text.text
    
    Text {
        id: text
    }

    standardButtons: StandardButton.Ok
}
