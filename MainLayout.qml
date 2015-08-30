import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQml.StateMachine 1.0
import QtMultimedia 5.4
import org.akazantsev 1.0

Item {
    id: root

    signal alarm()

    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight

    StateMachine {
        id: stateMachine
        initialState: normalState
        running: true

        State {
            id: normalState

            SignalTransition {
                targetState: runningState
                signal: controlButtons.actionClicked
            }
        }

        State {
            id: runningState
            onEntered: {
                countdownTimer.start();
                controlButtons.state = "running";
            }

            SignalTransition {
                targetState: alarmState
                signal: root.alarm
            }
        }

        State {
            id: pausedState
        }

        State {
            id: alarmState

            onEntered: {
                countdownTimer.pause();
                alarmSound.play();
                controlButtons.state = "alarm";
            }
        }
    }

    ColumnLayout {
        id: layout

        anchors.fill: parent

        TimeLabel {
            id: timeLabel

            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter
            time: countdownTimer.timeLeft
        }

        ControlButtons {
            id: controlButtons

            Layout.fillWidth: true
        }
    }

    MediaPlayer {
        id: alarmSound

        loops: MediaPlayer.Infinite
        source: "qrc:///sounds/alarm.ogg"
    }

    CountdownTimer {
        id: countdownTimer
        time: 20
    }
}

