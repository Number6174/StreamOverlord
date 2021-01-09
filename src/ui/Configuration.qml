// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.1

import StreamOverlord 1.0

Pane {
    id: root
    anchors.fill: parent

    AboutDialog {
        id: aboutDialog
    }
    DirectoriesDialog {
        id: directoriesDialog
    }

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

                Pane {
                    Layout.fillWidth: true
                    RowLayout {
                        Button {
                            text: "Directories"
                            onClicked: directoriesDialog.open()
                        }
                        Button {
                            text: "Check for Updates"
                        }
                        Button {
                            text: "Version Information"
                            onClicked: aboutDialog.open()
                        }
                    }
                }

                GroupBox {
                    Layout.fillWidth: true

                    title: "Twitch"
                    ColumnLayout {
                        anchors.fill: parent

                        // Token
                        Pane {
                            padding: 0
                            Layout.fillWidth: true
                            RowLayout {
                                anchors.fill: parent

                                Text {
                                    text: "Token: "
                                }
                                TextInput {
                                    id: twitchToken
                                    echoMode: twitchReveal.pressed ? TextInput.Normal : TextInput.Password
                                    Layout.fillWidth: true
                                    clip: true
                                    text: Backend.twitchToken
                                    onEditingFinished: Backend.twitchToken = twitchToken.text
                                }
                                Button {
                                    id: twitchReveal
                                    text: "Reveal"
                                }

                                Button {
                                    text: "Obtain"
                                    onClicked: Qt.openUrlExternally(
                                                   Backend.getTwitchImplicitOAuthURL(
                                                       ))
                                }
                                Button {
                                    text: "Revoke"
                                }
                            }
                        }
                    }
                }
            }
        }
        Pane {
            Layout.fillWidth: true

            RowLayout {
                Button {
                    text: "Save"
                    onClicked: Backend.writeConfiguration()
                }
                Button {
                    text: "Reload"
                    onClicked: Backend.readConfiguration()
                }
            }
        }
    }
}
