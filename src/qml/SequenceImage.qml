import QtQuick
import QtQuick.Layouts

StackLayout {
    id: root

    property alias running: timer.running
    property alias frameCount: root.count
    property alias currentFrame: root.currentIndex
    currentFrame: 0

    property real fps: 12

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
        interval: fps * 10
        running: false
        repeat: true
        onTriggered: incrementFrame()
        onIntervalChanged: {
            console.log("interval: ", interval)
        }
    }

    function incrementFrame() {
        let nextFrame = currentFrame + 1
        currentFrame = nextFrame === frames.length ? 0 : nextFrame
    }
}
