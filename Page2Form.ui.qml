import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 480
    height: 320

    Rectangle {
        id: rectangle
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: parent.width * .9
        height: parent.height * .8
        color: "#c4c4c4"
        Text {
            id: body
            text: qsTr("name")
            fontSizeMode: Text.Fit
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
        }
    }

    Rectangle {
        id: rectangle1
        x: 0
        y: 0
        width: parent.width * .8
        height: parent.height * .2
        color: "#2958ff"

        anchors.left: parent.left
        anchors.leftMargin: 10

        Text {
            id: name
            text: qsTr("name")
            color: "#ffffff"
            fontSizeMode: Text.Fit
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
        }
    }
}
