// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property alias model: mainList.model

    Component {
        id: eventDelegate
        Item {
            width: ListView.view.width
            height: 40
            Column {
                Text {
                    text: '<b>Time:</b> ' + time
                }
                Text {
                    text: '<b>Source:</b> ' + source
                }
            }
            MouseArea {
                id: mouseArea
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    mainList.currentIndex = index
                    mainList.forceActiveFocus()
                }
            }
            ToolTip {
                delay: 1000
                //ToolTip.timeout: 5000
                visible: mouseArea.containsMouse
                text: tooltip
            }
        }
    }

    ListView {
        id: mainList
        anchors.fill: parent

        delegate: eventDelegate
        highlightMoveDuration: 5
        highlight: Rectangle {
            color: "lightsteelblue"
            radius: 5
        }
        focus: true
        clip: true
        reuseItems: true
        ScrollBar.vertical: ScrollBar {}
    }
}
