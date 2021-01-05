// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Dialog {
    id: root
    width: 640
    height: 480
    title: "About Stream Overlord"
    ColumnLayout {
        anchors.fill: parent

        Text {
            text: "Stream Overlord 0.0.1"
        }
        Text {
            text: "Copyright 2021 Number6174"
        }

        RowLayout {
            Text {
                text: "Changes: "
            }
            ComboBox {
                model: ListModel {
                    id: versions
                    ListElement {
                        text: "0.0.1"
                    }
                }
                //width: 200
                onCurrentIndexChanged: getChanges(versions.get(
                                                      currentIndex).text)
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

    function getChanges(version) {
        var xmlhttp = new XMLHttpRequest()
        var url = "https://raw.githubusercontent.com/Number6174/StreamOverlord/main/dist/changes-"
                + version + ".md"

        xmlhttp.onreadystatechange = function () {
            if (xmlhttp.readyState == XMLHttpRequest.DONE
                    && xmlhttp.status == 200) {
                changesText.text = xmlhttp.responseText
            }
        }
        xmlhttp.open("GET", url, true)
        xmlhttp.send()
    }

    standardButtons: StandardButton.Close
}
