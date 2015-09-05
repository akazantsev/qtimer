import QtQuick 2.3
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
            suffix: "H"

            onTimeSetting: time += diff * 60 * 60
        }

        TimeUnit {
            id: minuteLabel
            editable: root.editable
            suffix: "M"

            onTimeSetting: time += diff * 60
        }

        TimeUnit {
            id: secondLabel
            editable: root.editable
            suffix: "S"

            onTimeSetting: time += diff
        }
    }

    onTimeChanged: {
        if (time < 0)
            time = 0;

        hourLabel.value = time / (60 * 60);
        minuteLabel.value = time / 60;
        secondLabel.value = time % 60;
    }
}

