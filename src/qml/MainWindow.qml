import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Squirrel
import SuperTux

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: Application.name



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

                Component.onCompleted: {
                    console.log(model)
                }
            }
        }

        TextEdit {
            id: codeedit

            Layout.fillWidth:  true
            Layout.fillHeight: true

            font.pointSize: 15
            font.family: "Consolas"
        }
    }

    SquirrelHighlighter {
        textDocument: codeedit.textDocument
    }
}
