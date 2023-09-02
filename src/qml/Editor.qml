import QtQuick
import QtQuick.Layouts

import Code
import Squirrel
import SuperTux

Item {
    id: root

    RowLayout {
        id: row

        anchors.fill: parent

        TreeView {
            Layout.fillHeight: true
            implicitWidth: 200
            alternatingRows: false


    /*
            model: FileSystemModel {
                rootPath: "/"
            }
    */



            model: LevelScriptsModel {
                levelFileName: "levels/test/swimming.stl"
            }


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
