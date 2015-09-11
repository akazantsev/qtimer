import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item {
    id: root

    property bool editable: false
    property int time: 0

    width: layout.implicitWidth
    height: layout.implicitHeight

    RowLayout {
        id: layout

        anchors.fill: parent
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
        minuteLabel.value = time / 60;
        secondLabel.value = time % 60;
    }
}

