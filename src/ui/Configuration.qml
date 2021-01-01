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
                                    //password: "asdf"
                                    onPasswordChanged: {

                                        changeNotifier.haveChanges = true
                                    }
                                }
                                Button {
                                    text: "Obtain"
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
                    onClicked: changeNotifier.haveChanges = false
                }

                Text {
                    id: changeNotifier
                    property var haveChanges: false
                    text: haveChanges ? "Unsaved changes exist" : "No unsaved"
                }
            }
        }
    }
}
