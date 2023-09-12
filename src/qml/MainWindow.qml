import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import Code
import Squirrel
import SuperTux

import "theme.js" as Theme

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: Application.name

    palette.button: Qt.darker(palette.button, 1.25)

    function _stripUrl(url) {
        return decodeURIComponent(url.toString().replace(/^(\w+:\/{3})/,""))
    }

    //FIXME
    // turn url relative to base
    function _rebasedUrl(base, url) {
        // quite cursed
        return (new URL(url.toString(), base)).toString()
    }

    FolderDialog {
        id: filedialog
        currentFolder: "/"
        onAccepted: editor.openFolder(_stripUrl(currentFolder))
    }

    FileDialog {
        id: leveldialog
        currentFolder: "/"
        onAccepted: editor.openLevel(_stripUrl(_rebasedUrl(".", currentFolder)))
    }

    header: MenuBar {
        font.pointSize: 11
        font.bold: true
        Menu {
            title: "File"

            MenuItem {
                text: "Open folder..."
                onTriggered: filedialog.open()
            }

            MenuItem {
                text: "Open level..."
                onTriggered: leveldialog.open()
            }
        }
    }

    property int currentMode: 0

    RowLayout {
        anchors.fill: parent

        Rectangle {

            component ModeButton : ToolButton {
                id: modebutton

                required property int index
                required property var modelData

                flat: true
                checkable: true
                icon.source: Theme.getIcon(modelData, checked)

                width: parent.width
                height: width
                background: Rectangle {
                    anchors.fill: parent
                    color: {
                        const buttoncolor = root.palette.button
                        if (modebutton.checked) return Qt.lighter(buttoncolor, 1.75)
                        if (modebutton.hovered) return Qt.lighter(buttoncolor, 1.25)
                        return buttoncolor
                    }
                }

                onPressed: {
                    root.currentMode = index
                }
            }

            color: root.palette.button
            Layout.fillHeight: true
            width: 50

            ButtonGroup {
                id: modeGroup
                exclusive: true

                Component.onCompleted: {
                    modeGroup.checkedButton = modeGroup.buttons[0]
                }
            }

            Column {
                anchors.fill: parent
                Repeater {
                    model: ["text", "edit"]
                    ModeButton {
                        ButtonGroup.group: modeGroup
                    }
                }
            }
        }

        StackLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: currentMode

            Editor {
                id: editor
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.centerIn: parent

                    AnimatedImage {
                        Layout.alignment: Qt.AlignCenter
                        source: "qrc:/images/tuxrun.gif"
                        playing: visible && root.active
                    }

                    Label {
                        Layout.alignment: Qt.AlignCenter
                        text: "SuperTux is starting up..."
                        font.pointSize: 11
                    }
                }
            }
        }

    }
}
