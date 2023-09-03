import QtQuick
import QtQuick.Controls
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

        ScrollView {
            id: scrollview
            Layout.fillWidth:  true
            Layout.fillHeight: true

            Flickable {
                flickDeceleration: 10000

                TextArea {
                    id: codeedit

                    cursorDelegate: TextCursor {}

                    font.pointSize: 15
                    font.family: "Consolas"
                }

                TextArea.flickable: codeedit
            }
        }
    }

    SquirrelHighlighter {
        textDocument: codeedit.textDocument
    }
}
