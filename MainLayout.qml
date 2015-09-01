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

            onEntered: {
                countdownTimer.reset();
                controlButtons.state = "normal";
            }

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
                targetState: normalState
                signal: controlButtons.resetClicked
            }

            SignalTransition {
                targetState: pausedState
                signal: controlButtons.actionClicked
            }

            SignalTransition {
                targetState: alarmState
                signal: countdownTimer.timeOut
            }
        }

        State {
            id: pausedState

            onEntered: {
                countdownTimer.pause();
                controlButtons.state = "paused";
            }

            SignalTransition {
                targetState: runningState
                signal: controlButtons.actionClicked
            }

            SignalTransition {
                targetState: normalState
                signal: controlButtons.resetClicked
            }
        }

        State {
            id: alarmState

            onEntered: {
                alarmSound.loops = 3;
                alarmSound.play();
                controlButtons.state = "alarm";
            }

            SignalTransition {
                targetState: normalState
                signal: controlButtons.actionClicked
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
            time: countdownTimer.timeLeft / 1000
        }

        ControlButtons {
            id: controlButtons

            Layout.fillWidth: true
        }
    }

    MediaPlayer {
        id: alarmSound

        loops: 10
        source: "qrc:///sounds/alarm.ogg"
    }

    CountdownTimer {
        id: countdownTimer
        duration: 20
    }
}

