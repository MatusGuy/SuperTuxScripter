import QtQuick
import QtQuick.Controls

import Squirrel 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 800
    title: Application.name

    TextEdit {
        id: codeedit

        anchors.fill: parent

        font.pointSize: 15
        font.family: "Consolas"
    }

    SquirrelHighlighter {
        textDocument: codeedit.textDocument
    }
}
