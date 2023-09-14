import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Code
import Squirrel
import SuperTux

StackLayout {
    id: root
    currentIndex: 0

    property url currentFile: ""

    // TODO: Implement QML Loader instead!
    function fileTypeId(type) {
        if (type === "") return 0;
        switch (type) {
            case "nut": return 1;
            case "sprite": return 2;
            default: return 1;
        }
    }

    function open(itemurl) {
        let filetype = itemurl.toString().replace(/^\w*\.(?=\w)/, "");
        root.currentIndex = fileTypeId(filetype);
        root.currentFile = itemurl
    }

    Item { id: empty }

    ScrollView {
        id: scrollview
        anchors.fill: parent

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

        SquirrelHighlighter {
            textDocument: codeedit.textDocument
        }
    }

    SplitView {
        id: spriteviewer
        anchors.fill: parent
        orientation: Qt.Vertical

        Item {
            SplitView.fillHeight: true
        }

        GridView {
            SplitView.preferredHeight: 100
            model: ListModel {
                id: fruitModel

                ListElement {
                    name: "run"
                }
                ListElement {
                    name: "jump"
                }
                ListElement {
                    name: "crouch"
                }
            }
        }
    }
}
