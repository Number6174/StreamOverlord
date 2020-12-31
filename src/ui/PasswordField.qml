// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

RowLayout {
    property alias password: passwordText.text
    TextInput {
        id: passwordText
        echoMode: button.pressed ? TextInput.Normal : TextInput.Password
        Layout.fillWidth: true
    }
    Button {
        id: button
        text: "Reveal"
    }
}
