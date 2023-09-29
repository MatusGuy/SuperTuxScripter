import QtQuick
import QtQuick.Layouts

StackLayout {
    id: root

    property alias frameCount: root.count
    property alias currentFrame: root.currentIndex
    currentFrame: 0

    property bool running: false

    required property list<url> frames

    Repeater {
        model: frames

        Image {
            required property url modelData
            source: modelData
        }
    }

    Timer {
        id: timer
        interval: 100
        running: root.running
        repeat: true
        onTriggered: incrementFrame()
    }

    function incrementFrame() {
        let nextFrame = currentFrame + 1
        currentFrame = nextFrame === frames.length ? 0 : nextFrame
        console.log("change frame: ", currentFrame)
    }
}
