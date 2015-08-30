import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    id: root

    signal actionClicked()
    signal resetClicked()

    height: buttonLayout.implicitHeight
    state: "normal"
    states: [
        State {
            name: "normal"
            PropertyChanges { target: resetButton; enabled: false    }
        },
        State {
            name: "paused"
            PropertyChanges { target: actionButton; state:  "start"  }
        },
        State {
            name: "running"
            PropertyChanges { target: actionButton; state:  "pause"  }
            PropertyChanges { target: resetButton;  enabled: true    }
        },
        State {
            name: "alarm"
            PropertyChanges { target: actionButton; enabled: false   }
            PropertyChanges { target: resetButton;  state:  "disarm" }
        }
    ]

    RowLayout {
        id: buttonLayout

        anchors.fill: parent

        Button {
            id: actionButton

            Layout.fillWidth: true
            state: "start"
            states: [
                State {
                    name: "start"
                    PropertyChanges {
                        target: actionButton
                        text: "&Start"
                        iconName: "media-playback-start"
                    }
                },
                State {
                    name: "pause"
                    PropertyChanges {
                        target: actionButton
                        text: "&Pause"
                        iconName: "media-playback-pause"
                    }
                }
            ]
            onClicked: root.actionClicked()
        }

        Button {
            id: resetButton

            Layout.fillWidth: true
            state: "reset"
            states: [
                State {
                    name: "reset"
                    PropertyChanges {
                        target: resetButton
                        text: "&Reset"
                        iconName: "media-playback-stop"
                    }
                },
                State {
                    name: "disarm"
                    PropertyChanges {
                        target: resetButton
                        text: "&Disarm"
                    }
                }
            ]
            onClicked: root.resetClicked()
        }
    }
}

