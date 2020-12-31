// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.1

import StreamOverlord 1.0
//import AboutDialog

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: "Stream Overlord"

    AboutDialog {
        id: aboutDialog
    }
    DirectoriesDialog {
        id: directoriesDialog
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"
            Action {
                text: "Configure &Directories"
                onTriggered: directoriesDialog.open()
            }

            Action {
                text: "&Quit"
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: "&Help"
            Action {
                text: "Check for &Updates"
            }
            Action {
                text: "&About"

                onTriggered: aboutDialog.open()
            }
        }
    }

    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }

    header: Text {
        text: "Connection status stuff goes here"
    }

    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop

            Button {
                text: "Config"
                Layout.alignment: Qt.AlignHCenter
                onClicked: loader.setSource("Configuration.qml")
                //onClicked: loader.setSource("config.qml", {"opacity": 1})
                //onClicked: loader.source = "config.qml"
            }
            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Main Queue"
                onClicked: loader.sourceComponent = blue
            }
            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Marathon Timer"
                onClicked: loader.sourceComponent = green
            }
        }

        Loader {
            id: loader
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: "Configuration.qml"
        }
    }

    Component {
        id: blue
        Rectangle {
            anchors.fill: parent

            color: "blue"
        }
    }
    Component {
        id: green
        Rectangle {
            anchors.fill: parent

            color: "green"
        }
    }


    /*
        // Listview
        EventList {
            width: parent.width
            height: parent.height - twitchPane.height - logPane.height

            model: EventModel {}
        }
*/
}
