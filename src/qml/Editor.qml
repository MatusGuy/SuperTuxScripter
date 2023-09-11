import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Code
import Squirrel
import SuperTux

Item {
    id: root

    SplitView {
        id: row
        anchors.fill: parent
        orientation: Qt.Horizontal

        TreeView {
            height: parent.height
            SplitView.preferredWidth: 200
            clip: true
            alternatingRows: false
            flickDeceleration: 10000
            columnWidthProvider: (column) => {
                if (column > 0) return 0 // hide column
                return -1 // default size
            }

            ScrollBar.vertical: ScrollBar {}
            ScrollBar.horizontal: ScrollBar {}

            model: FileSystemModel {
                rootPath: "/"
            }


/*
            model: LevelScriptsModel {
                levelFileName: "levels/my_world/semisol.stl"
            }
*/

            delegate: InspectorDelegate {
                displayRoleName: "fileName"
            }
        }

        ScrollView {
            id: scrollview
            height: parent.height
            SplitView.fillWidth: true

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
