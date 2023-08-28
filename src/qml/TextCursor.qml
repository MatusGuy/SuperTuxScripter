import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes

import Squirrel
import SuperTux

Item {
    width: 1
    Rectangle {
        id: rectangle
        color: "white"
        y: 1
        width: 2
        height: parent.height - 2
        SequentialAnimation on opacity {
            id: curanim
            loops: Animation.Infinite
            running: window.active // only run animation when active window

            readonly property int time: 500

            PropertyAnimation { to: 0.0; duration: curanim.time; easing.type: Easing.OutQuad }
            PropertyAnimation { to: 1.0; duration: curanim.time; easing.type: Easing.OutQuad }
        }
    }
}
