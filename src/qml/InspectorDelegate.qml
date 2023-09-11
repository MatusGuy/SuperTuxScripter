import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

TreeViewDelegate {
    id: root

    property string displayRoleName: "display";

    contentItem : Row {
        spacing: 5

        Component {
            id: iconComponent
            Image {
                id: icon
                source: model.decoration
            }
        }

        Loader {
            // Only load icon if model has a decoration role
            sourceComponent: model.decoration === undefined ? null : iconComponent
        }

        Label {
            id: label
            height: icon.height
            text: model[displayRoleName]
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            color: highlighted ? palette.highlightedText : palette.buttonText
            visible: !editing
        }
    }
}
