import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item {
    id: root

    property int time: 0

    width: layout.implicitWidth
    height: layout.implicitHeight

    RowLayout {
        id: layout

        anchors.fill: parent
        spacing: 10

        TimeUnit {
            id: hourLabel
            suffix: "H"
        }

        TimeUnit {
            id: minuteLabel
            suffix: "M"
        }

        TimeUnit {
            id: secondLabel
            suffix: "S"
        }
    }

    onTimeChanged: {
        hourLabel.value = time / (60 * 60);
        minuteLabel.value = time / 60;
        secondLabel.value = time % 60;
    }
}

