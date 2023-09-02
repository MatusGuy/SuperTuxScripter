import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes

import Code
import Squirrel
import SuperTux

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: Application.name

    header: MenuBar {
        font.pointSize: 11
        Menu {
            title: "File"

            MenuItem {
                text: "Open"
            }
        }
    }

    RowLayout {
        anchors.fill: parent

        Rectangle {

            component ModeButton : ToolButton {
                id: modebutton
                icon.source: modelData
                flat: true
                checkable: true

                width: parent.width
                height: width
                background: Rectangle {
                    anchors.fill: parent
                    color: {
                        const buttoncolor = root.palette.button
                        if (modebutton.checked) return Qt.darker(buttoncolor, 1.75)
                        if (modebutton.hovered) return Qt.darker(buttoncolor, 1.25)
                        return buttoncolor
                    }
                }
            }

            color: root.palette.button
            Layout.fillHeight: true
            width: 50

            ButtonGroup {
                id: modeGroup
                exclusive: true
            }

            Column {
                anchors.fill: parent
                Repeater {
                    model: ["qrc:/images/text.svg", "qrc:/images/edit.svg"]
                    ModeButton {
                        ButtonGroup.group: modeGroup
                    }
                }
            }
        }

        StackLayout {
            Editor {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

    }
}
