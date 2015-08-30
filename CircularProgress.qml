import QtQuick 2.4

Item {
    id: root

    property int min: 0
    property int max: 100
    property int value: 0
    property int circleWidth: 8
    property Component progressMarker

    Rectangle {
        id: face

        property int size: Math.min(parent.width, parent.height) -
                           (marker.width - border.width)
        width: size
        height: size

        anchors.centerIn: parent
        radius: size / 2
        color: "transparent"
        border.width: circleWidth
        border.color: "steelblue"

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.width: 1
            border.color: "red"
        }

        Loader {
            id: marker
            x: (face.size - marker.width) / 2
            y: (circleWidth - marker.width) / 2;
            transform: Rotation {
                origin.x: marker.width / 2
                origin.y: (face.size + marker.width) / 2
                angle: 360 * (value - min) / max
            }

            sourceComponent: progressMarker
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.width: 1
        border.color: "green"
    }

    Rectangle {
        width: 2
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"
        border.width: 1
        border.color: "blue"
    }
}

