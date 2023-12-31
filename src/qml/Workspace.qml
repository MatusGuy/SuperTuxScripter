import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Code
import Squirrel
import SuperTux

Item {
    id: root

    FileSystemModel {
        id: filesystemmodel
        rootPath: "/mnt/data/Games/SuperTux/"
    }

    LevelScriptsModel {
        id: levelmodel
        levelFileName: "levels/my_world/semisol.stl"
    }

    property alias _model: inspector.model
    _model: filesystemmodel

    SplitView {
        id: row
        anchors.fill: parent
        orientation: Qt.Horizontal

        TreeView {
            id: inspector
            height: parent.height
            SplitView.preferredWidth: 200
            clip: true
            alternatingRows: false
            flickDeceleration: 10000
            selectionBehavior: TreeView.SelectRows
            columnWidthProvider: (column) => {
                if (column > 0) return 0 // hide column
                return -1 // default size
            }

            selectionModel: ItemSelectionModel {
                model: inspector.model
            }

            ScrollBar.vertical: ScrollBar {}
            ScrollBar.horizontal: ScrollBar {}

            delegate: InspectorDelegate {
                id: insdel
                //displayRoleName: model === filesystemmodel ? "fileName"
                onDoubleClicked: {
                    editor.open("file://"+insdel.model.toolTip)
                }
            }
        }

        Editor {
            id: editor
            SplitView.fillWidth: true
            height: parent.height
        }
    }

    function openFolder(url) {
        //FIXME
        //filesystemmodel.rootPath = url
        _model = filesystemmodel
    }

    function openLevel(level) {
        //FIXME
        //levelmodel.levelFileName = level
        _model = levelmodel
    }
}
