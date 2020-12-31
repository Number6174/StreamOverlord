// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.1

Dialog {
    id: root
    title: "Directories for logs and configuration files"

    GridLayout {
        anchors.fill: parent
        columns: 3

        // Log files
        Text {
            text: "Log files: "
        }
        TextInput {
            id: logDirectoryTextInput
            Layout.fillWidth: true
            Settings {
                property alias logDirectory: logDirectoryTextInput.text
            }
        }
        Button {
            text: "Select"
            icon.name: "document-open"
            onClicked: logDirectoryDialog.open()
        }

        FileDialog {
            id: logDirectoryDialog
            title: "Select a directory for log files"
            folder: shortcuts.documents
            selectFolder: true
            onAccepted: {
                logDirectoryTextInput.text = logDirectoryDialog.fileUrl
            }
        }

        // Configuration files
        Text {
            text: "Configuration files: "
        }
        TextInput {
            id: configDirectoryTextInput
            Settings {
                property alias configDirectory: configDirectoryTextInput.text
            }
            Layout.fillWidth: true
        }
        Button {
            text: "Select"
            icon.name: "document-open"
            onClicked: configDirectoryDialog.open()
        }

        FileDialog {
            id: configDirectoryDialog
            title: "Select a directory for configuration files"
            folder: shortcuts.documents
            selectFolder: true
            onAccepted: {
                configDirectoryTextInput.text = configDirectoryDialog.fileUrl
            }
        }

        Text {
            Layout.columnSpan: 3
            text: "These values are automatically saved in the registry on Windows (HKCU\\Software\\Number6174\\Stream Overlord)"
        }
    }
}
