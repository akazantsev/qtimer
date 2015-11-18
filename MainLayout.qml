import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQml.StateMachine 1.0
import QtMultimedia 5.5

import org.akazantsev 1.0
import Qt.labs.settings 1.0

Item {
    id: root

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
                timeView.editable = true;
            }

            onExited: timeView.editable = false


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
                alarmSound.play();
                controlButtons.state = "alarm";
            }

            onExited: alarmSound.stop()

            SignalTransition {
                targetState: normalState
                signal: controlButtons.actionClicked
            }
        }
    }

    ColumnLayout {
        id: layout

        anchors.fill: parent

        TimeView {
            id: timeView
            Layout.fillWidth: true
            Layout.fillHeight: true

            model: CountdownTimer {
                id: countdownTimer
                duration: 20

                // Can't be binded
                onTimeLeftChanged: updateTime()
                Component.onCompleted: updateTime()

                function updateTime() {
                    timeView.time = timeLeft / 1000;
                }
            }

            onTimeChanged: {
                if (editable)
                    countdownTimer.duration = time;
            }
        }

        ControlButtons {
            id: controlButtons

            Layout.fillWidth: true
        }
    }

    Audio {
        id: alarmSound

        loops: Audio.Infinite
        source: "qrc:///sounds/alarm.ogg"
    }
}

