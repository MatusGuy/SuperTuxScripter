import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import SuperTux

Item {
    id: root

    ColumnLayout {
        anchors.centerIn: parent

        AnimatedImage {
            Layout.alignment: Qt.AlignCenter
            source: "qrc:/images/tuxrun.gif"
            playing: visible && root.active
        }

        StackLayout {
            id: stack
            Layout.alignment: Qt.AlignCenter
            currentIndex: 0

            Button {
                text: "Start SuperTux"
                font.pointSize: 11
                onClicked: {
                    SuperTuxThread.startSuperTux();
                    stack.currentIndex = 1;
                }
            }

            Label {
                text: "SuperTux is starting up..."
                font.pointSize: 11
            }
        }
    }
}
