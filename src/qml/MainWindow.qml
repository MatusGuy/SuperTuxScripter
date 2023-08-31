import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes

import Code
import Squirrel
import SuperTux

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: Application.name

    header: MenuBar {
        Menu {
            title: "File"

            MenuItem {
                text: "Open"
            }
        }
    }

    RowLayout {
        anchors.fill: parent

        TreeView {
            Layout.fillHeight: true
            implicitWidth: 200
            alternatingRows: false



            model: FileSystemModel {
                rootPath: "/"
            }


/*
            model: LevelScriptsModel {
                levelFileName: "levels/test/swimming.stl"
            }
*/

            delegate: InspectorDelegate {}
        }

        TextEdit {
            id: codeedit

            Layout.fillWidth:  true
            Layout.fillHeight: true

            cursorDelegate: TextCursor {}

            font.pointSize: 15
            font.family: "Consolas"
        }
    }

    SquirrelHighlighter {
        textDocument: codeedit.textDocument
    }
}
