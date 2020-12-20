// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2

import StreamOverlord 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: "Stream Overlord"

    Column {
        id: rowLayout
        width: parent.width
        height: parent.height

        // Log selection
        Item {
            id: logPane
            width: parent.width
            height: 30
            Text {
                id: logFileText
                text: "Log file: "
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            TextInput {
                id: logFileName
                height: 14
                anchors.left: logFileText.right
                anchors.right: logFileOpenButton.left
                anchors.verticalCenter: parent.verticalCenter
            }
            Button {
                id: logFileOpenButton
                height: 14
                text: "Open"
                icon.name: "document-open"
                onClicked: fileOpenDialog.open()
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        // Twitch Pane
        Item {
            id: twitchPane
            width: parent.width
            height: 30
            Text {
                id: twitchText
                text: "Twitch token: "
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            TextInput {
                id: twitchToken
                height: 14
                anchors.left: twitchText.right
                anchors.right: twitchConnectButton.left
                anchors.verticalCenter: parent.verticalCenter
            }
            Button {
                id: twitchConnectButton
                height: 14
                text: "Connect"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        // Listview
        EventList {
            width: parent.width
            height: parent.height - twitchPane.height - logPane.height

            model: EventModel {}
                /*ListModel {
                ListElement {
                    name: "Bill Smith"
                    number: "555 3264"
                }
                ListElement {
                    name: "John Brown"
                    number: "555 8426"
                }
                ListElement {
                    name: "Sam Wise"
                    number: "555 0473"
                }
                ListElement {
                    name: "Bill Smith"
                    number: "555 3264"
                }
                ListElement {
                    name: "John Brown"
                    number: "555 8426"
                }
                ListElement {
                    name: "Sam Wise"
                    number: "555 0473"
                }
                ListElement {
                    name: "Bill Smith"
                    number: "555 3264"
                }
                ListElement {
                    name: "John Brown"
                    number: "555 8426"
                }
                ListElement {
                    name: "Sam Wise"
                    number: "555 0473"
                }
                ListElement {
                    name: "Bill Smith"
                    number: "555 3264"
                }
                ListElement {
                    name: "John Brown"
                    number: "555 8426"
                }
                ListElement {
                    name: "Sam Wise"
                    number: "555 0473"
                }
            }
            */
        }
    }

    FileDialog {
        id: fileOpenDialog
        title: "Select a log file"
        folder: shortcuts.documents
        nameFilters: ["Log file (*.txt *.log)"]
        onAccepted: {
            logFileName.text = fileOpenDialog.fileUrl
        }
    }
}
