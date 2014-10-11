import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

Window {
    visible: true
    width: 360
    height: 360

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    ColumnLayout {
        anchors.fill: parent

        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            columns: gridWidthSlider.value
            Repeater {
                model: gridWidthSlider.value * gridWidthSlider.value

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "blue"
                }
            }
        }

        Slider {
            id: gridWidthSlider
            minimumValue: 4.0
            maximumValue: 64.0
            stepSize: 1.0
            Layout.fillWidth: true
        }
    }
}