import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    id: root

    height: buttonLayout.implicitHeight
    state: "normal"
    states: [
        State {
            name: "normal"

            PropertyChanges {
                target: actionButton
                text: "&Start"
                iconName: "media-playback-start"
            }
            PropertyChanges { target: resetButton; enabled: false    }
        },
        State {
            name: "paused"

            PropertyChanges {
                target: actionButton
                text: "&Start"
                iconName: "media-playback-start"
            }
        },
        State {
            name: "running"

            PropertyChanges {
                target: actionButton
                text: "&Pause"
                iconName: "media-playback-pause"
            }
            PropertyChanges { target: resetButton;  enabled: true    }
        },
        State {
            name: "alarm"

            PropertyChanges {
                target: actionButton
                text: "&Disarm"
            }
            PropertyChanges { target: resetButton;  enabled: false   }
        }
    ]

    RowLayout {
        id: buttonLayout

        anchors.fill: parent

        Button {
            id: actionButton

            Layout.fillWidth: true
            onClicked: actionClicked()
        }

        Button {
            id: resetButton

            Layout.fillWidth: true
            text: "&Reset"
            iconName: "media-playback-stop"
            onClicked: root.state = "normal"
        }
    }

    function actionClicked() {
        if (state == "normal" || state == "paused")
            state = "running";
        else if (state == "running")
            state = "paused";
        else if (state == "alarm")
            state = "normal";
    }
}

