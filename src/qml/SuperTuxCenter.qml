import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import SuperTux

Item {
    id: root

    StackLayout {
        id: stack
        currentIndex: 1

        SuperTuxViewport {
            Layout.fillWidth: true
            Layout.fillHeight: true
            t: 1
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignCenter

            AnimatedImage {
                Layout.alignment: Qt.AlignCenter
                source: "qrc:/images/tuxrun.gif"
                playing: visible && root.active
            }

            StackLayout {
                id: status
                Layout.alignment: Qt.AlignCenter
                currentIndex: 0

                Button {
                    text: "Start SuperTux"
                    font.pointSize: 11
                    onClicked: {
                        SuperTuxThread.startSuperTux();
                        status.currentIndex = 1;
                        stack.currentIndex = 0;
                    }
                }

                Label {
                    text: "SuperTux is starting up..."
                    font.pointSize: 11
                }
            }
        }
    }
}
