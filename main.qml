import QtQuick 2.4
import QtQuick.Controls 1.2

ApplicationWindow {
    id: root
    width: 300
    height: width
    visible: true
    title: "QML Window"

    CircularProgress {
        anchors.fill: parent
        anchors.margins: 20

        progressMarker: Rectangle {
            width: 20
            height: 20
            radius: face.radius * 5
            color: "steelblue"
        }
    }
}
