import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtMultimedia 5.5

import org.akazantsev 1.0
import Qt.labs.settings 1.0

Item {
    id: root

    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight

    ColumnLayout {
        id: layout

        anchors.fill: parent

        TimeView {
            id: timeView
            Layout.fillWidth: true
            Layout.fillHeight: true
            editable: controlButtons.state == "normal"

            model: CountdownTimer {
                id: countdownTimer

                duration: 20
                running: controlButtons.state == "running"

                onTimeOut: {
                    controlButtons.state = "alarm";
                    alarmSound.play();
                }
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

            onStateChanged: {
                if (state == "normal")
                {
                    alarmSound.stop();
                    countdownTimer.reset();
                }
            }
        }
    }

    Audio {
        id: alarmSound

        loops: Audio.Infinite
        source: "qrc:///sounds/alarm.ogg"
    }
}

