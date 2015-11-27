import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    id: root

    height: buttonLayout.implicitHeight
    state: "normal"
    states: [
        State {
            name: "paused"

            PropertyChanges {
                target: resetButton
                enabled: true
            }
        },
        State {
            name: "running"

            PropertyChanges {
                target: actionButton
                text: "&Pause"
                iconName: "media-playback-pause"
            }

            PropertyChanges {
                target: resetButton
                enabled: true
            }
        },
        State {
            name: "alarm"

            PropertyChanges {
                target: actionButton
                text: "&Disarm"
            }
        }
    ]

    RowLayout {
        id: buttonLayout

        anchors.fill: parent

        Button {
            id: actionButton

            Layout.fillWidth: true
            text: "&Start"
            iconName: "media-playback-start"

            onClicked: actionClicked()
        }

        Button {
            id: resetButton

            Layout.fillWidth: true
            enabled: false
            text: "&Reset"
            iconName: "media-playback-stop"

            onClicked: root.state = "normal"
        }
    }

    function actionClicked() {
        var transitions = {
            "normal":  "running",
            "paused":  "running",
            "running": "paused",
            "alarm":   "normal"
        };

        state = transitions[state];
    }
}

