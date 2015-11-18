import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import org.akazantsev 1.0

Item {
    id: root

    property bool editable: false
    property int time: 0
    property var model

    width: circularProgress.size + 20
    height: circularProgress.size + 20

    CircularProgress {
        id: circularProgress

        property int size: Math.max(layout.implicitWidth, layout.implicitHeight) + 2 * penWidth + 20
        anchors.centerIn: parent
        width: size
        height: size
        value: (model.timeLeft / (model.duration * 1000.0)) * 360 * 16
        color: "steelblue"
    }

    RowLayout {
        id: layout

        anchors.centerIn: parent
        spacing: 10

        TimeUnit {
            id: hourLabel

            editable: root.editable
            postfix: "H"
            onTimeSetting: time += diff * 60 * 60
        }

        TimeUnit {
            id: minuteLabel

            editable: root.editable
            postfix: "M"
            onTimeSetting: time += diff * 60
        }

        TimeUnit {
            id: secondLabel

            editable: root.editable
            postfix: "S"
            onTimeSetting: time += diff
        }
    }

    onTimeChanged: {
        if (time < 0)
            time = 0;

        var t = time;
        hourLabel.value = t / (60 * 60);
        t %= 60 * 60;
        minuteLabel.value = t / 60;
        secondLabel.value = t % 60;
    }
}

