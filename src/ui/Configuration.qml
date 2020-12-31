// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.1

Pane {
    id: root
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        ScrollView {
            clip: true
            width: parent.width
            Layout.fillWidth: true
            Layout.fillHeight: true
            contentWidth: availableWidth
            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                GroupBox {
                    Layout.fillWidth: true
                    label: CheckBox {
                        id: twitchCheckBox
                        checked: true
                        text: "Twitch"
                    }
                    ColumnLayout {
                        anchors.fill: parent
                        enabled: twitchCheckBox.checked

                        // Token
                        Pane {
                            padding: 0
                            Layout.fillWidth: true
                            RowLayout {
                                anchors.fill: parent

                                Text {
                                    text: "Twitch token: "
                                }
                                PasswordField {
                                    id: twitchToken
                                    password: "asdf"
                                }
                                Button {
                                    text: "Obtain Token"
                                }
                            }
                        }
                    }
                }
            }
        }
        Pane {
            Layout.fillWidth: true

            Button {
                text: "Save"
            }
        }
    }
}
