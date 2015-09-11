import QtQuick 2.5
import QtQuick.Controls 1.2

Item {
    id: root

    width: (valueMetrics.width + 8) + postfixMetrics.width
    height: valueMetrics.height

    signal timeSetting(int diff)

    property bool editable: false
    property int value: 0
    property alias text: valueLabel.text
    property alias postfix: postfixLabel.text
    property string fontFamily: "Sans"

    Label {
        id: valueLabel

        anchors.top: parent.top
        anchors.right: postfixLabel.left
        text: ("00" + Math.floor(value)).substr(-2, 2)
        font.pointSize: 42
        font.family: fontFamily

        TextMetrics {
            id: valueMetrics

            font.pointSize: valueLabel.font.pointSize
            font.family: fontFamily
            text: "00"
        }
    }

    Label {
        id: postfixLabel

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 5
        font.pointSize: 18
        font.family: fontFamily

        TextMetrics {
            id: postfixMetrics

            font.pointSize: postfixLabel.font.pointSize
            font.family: fontFamily
            text: postfixLabel.text
        }
    }

    MouseArea {
        anchors.fill: parent

        property var wheelState: { "delta": 0, "sensivity": 120 }
        property var mouseState: { "delta": 0, "sensivity": 30, "prevPos": 0 }

        onPressed: {
            if (!editable)
                return;

            if (mouse.buttons & Qt.LeftButton)
                mouseState.prevPos = mouse.y;
        }

        onPositionChanged: {
            if (!editable)
                return;

            if (!(mouse.buttons & Qt.LeftButton))
                return;

            mouseState.delta += mouseState.prevPos - mouse.y;
            mouseState.prevPos = mouse.y;

            checkValueChange(mouseState);
        }

        onWheel: {
            if (!editable)
                return;

            wheelState.delta += wheel.angleDelta.y;

            checkValueChange(wheelState);
        }

        function checkValueChange(input) {
            if (Math.abs(input.delta) >= input.sensivity)
            {
                root.timeSetting(toInt(input.delta / input.sensivity));
                input.delta %= input.sensivity;
            }
        }

        function toInt(value) {
            if (value >= 0)
                return Math.floor(value);

            return Math.ceil(value);
        }
    }
}

