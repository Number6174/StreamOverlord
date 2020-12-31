// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import StreamOverlord 1.0

Dialog {
    id: root
    title: "Directories for logs and configuration files"
    standardButtons: Dialog.RestoreDefaults | Dialog.Ok

    onReset: Backend.defaultDirectorySettings()

    GridLayout {
        anchors.fill: parent
        columns: 3

        // Configuration files
        Text {
            text: "Configuration files: "
        }
        TextInput {
            id: configDirectoryTextInput
            text: Backend.configDirectory
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
                Backend.configDirectory = Backend.convertURLtoPath(configDirectoryDialog.fileUrl)
            }
        }

        // Log files
        Text {
            text: "Log files: "
        }
        TextInput {
            id: logDirectoryTextInput
            text: Backend.logDirectory
            Layout.fillWidth: true
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
                Backend.logDirectory = Backend.convertURLtoPath(logDirectoryDialog.fileUrl)
            }
        }
    
        Text {
            Layout.columnSpan: 3
            text: "These values are automatically saved in the registry on Windows (HKCU\\Software\\Number6174\\Stream Overlord)"
        }
    }
}
