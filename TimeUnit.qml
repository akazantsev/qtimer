import QtQuick 2.3
import QtQuick.Controls 1.2

Item {
    id: root

    width: valueLabel.implicitWidth + suffixLabel.implicitWidth
    height: valueLabel.implicitHeight

    property int value: 0
    property alias text: valueLabel.text
    property alias suffix: suffixLabel.text

    Label {
        id: valueLabel

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        text: ("00" + Math.floor(value)).substr(-2, 2)
        font.pointSize: 42
        font.family: "Monospaced"
    }

    Label {
        id: suffixLabel

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: valueLabel.right
        anchors.right: parent.right

        anchors.topMargin: 5
        font.pointSize: 18
    }
}

