import QtQuick
import QtQuick.Controls

TreeViewDelegate {
    id: root

    property var arrow: indicator
    Image {
        id: itemIcon
        source: "qrc:/images/object.svg" }
    indicator: Row {
        children: [
            arrow,
            itemIcon
        ]
    }
}
