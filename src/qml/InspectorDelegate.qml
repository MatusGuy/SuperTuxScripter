import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "theme.js" as Theme

TreeViewDelegate {
    id: root

    required property int column

    property string displayRoleName: "display";

    contentItem : Row {
        spacing: 5

        Image {
            id: icon
            source: Theme.getIcon(model.decoration)
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

    ToolTip.delay: 1500
    ToolTip.visible: hovered
    ToolTip.text: model.toolTip
}
