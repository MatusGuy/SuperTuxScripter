import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes

import Squirrel
import SuperTux

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: Application.name

    Material.theme: Material.Dark

    RowLayout {
        anchors.fill: parent

        TreeView {
            Layout.fillHeight: true
            implicitWidth: 200


            model: LevelScriptsModel {
                id: levelModel
            }
            delegate: Label {
                text: model.name
            }
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
