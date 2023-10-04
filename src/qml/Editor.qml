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
        let filetype = itemurl.toString().replace(/^.*\.(?=\w)/, "");
        root.currentFile = itemurl
        root.currentIndex = fileTypeId(filetype);
    }

    Item { id: empty }

    ScrollView {
        id: scrollview
        Layout.fillHeight: true
        Layout.fillWidth: true

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
        Layout.fillHeight: true
        Layout.fillWidth: true
        orientation: Qt.Vertical

        Item {
            SplitView.fillHeight: true

            SequenceImage {
                id: sprite
                frames: []
                running: false
            }
        }

        GridView {
            width: parent.width
            SplitView.preferredHeight: 100
            model: SpriteModel {
                spriteFile: currentFile
            }
            delegate: Button {
                contentItem: Column {
                    Image {
                        source: model.decoration
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: model.display
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                onDoubleClicked: {
                    sprite.frames = model.frames
                    sprite.fps = model.fps
                    sprite.running = true
                }
            }
        }
    }
}
