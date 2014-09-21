import QtQuick 2.3

Rectangle {
    width: 800
    height: 600
    color: "lightblue"

    Item {
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Text {
            id: t1
            anchors.top: parent.top
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            text: "hello all folks"
            font.pixelSize: 28
        }
        Text {
            id: t2
            anchors.top: t1.bottom
            anchors.topMargin: 5
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            text: "Hahaha in the middle"
            font.pixelSize: 42
        }
        Text {
            anchors.top: t2.bottom
            anchors.topMargin: 5
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            text: "I am a sligthly longer text for enjoyment"
            font.pixelSize: 16
        }
    }
}
