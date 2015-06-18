import QtQuick 2.4

Item {
    id: root

    property Component progressMarker

    Rectangle {
        id: face

        width: Math.min(parent.width, parent.height) - marker.width
        height: width

        anchors.centerIn: parent
        radius: width / 2
        color: "transparent"
        border.width: 8
        border.color: "skyblue"
    }

    Loader {
        id: marker

        sourceComponent: progressMarker
        y: face.y - width / 2 + face.border.width / 2
        anchors.horizontalCenter: face.horizontalCenter
    }
}

