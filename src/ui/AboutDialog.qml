// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import StreamOverlord 1.0

Dialog {
    id: root
    width: 640
    height: 480
    title: "About Stream Overlord"

    ColumnLayout {
        anchors.fill: parent

        Text {
            text: "Stream Overlord " + Backend.getCurrentVersion()
        }
        Text {
            text: "Copyright 2021 Number6174"
        }

        RowLayout {
            Text {
                text: "Changes: "
            }
            ComboBox {
                id: versions
                model: ChangesModel {}
                textRole: "versionNumber"
                onCurrentIndexChanged: changesText.text = versions.model.getURIContents(currentIndex)
            }
        }

        ScrollView {
            clip: true
            width: parent.width
            //Layout.fillWidth: true
            Layout.fillHeight: true
            contentWidth: availableWidth

            TextEdit {
                id: changesText
                width: parent.width
                textFormat: TextEdit.MarkdownText
                readOnly: true
            }
        }
    }

    standardButtons: StandardButton.Close
}
