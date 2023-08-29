import QtQuick

Item {
    id: root

    visible: parent.activeFocus
    width: 1
    Rectangle {
        id: rectangle
        color: "black"
        y: 1
        width: 2
        height: parent.height - 2

        SequentialAnimation on opacity {
            id: curanim
            loops: Animation.Infinite
            running: root.parent.activeFocus // only run animation when active textedit

            readonly property int time: 500

            PropertyAnimation { to: 0.0; duration: curanim.time; easing.type: Easing.OutQuad }
            PropertyAnimation { to: 1.0; duration: curanim.time; easing.type: Easing.OutQuad }
        }
    }
}
