import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

TreeViewDelegate {
    id: root

    contentItem : Row {
        spacing: 5

        Image {
            id: icon
            source: model.decoration
        }

        Label {
            id: label
            height: icon.height
            clip: false
            text: model.display
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            color: highlighted ? palette.highlightedText : palette.buttonText
            visible: !editing
        }
    }
}
