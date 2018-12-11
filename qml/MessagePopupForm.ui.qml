import QtQuick 2.4
import QtQuick.Controls 2.4

Popup {
    id: popup
    //    activeFocus: true
    focus: true
    modal: true

    property string name

    Rectangle {
        id: bodyBox
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
            font.pointSize: 30
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
        id: nameBox
        width: parent.width * .8
        height: parent.height * .2
        color: "#2958ff"
        anchors.left: parent.left
        anchors.leftMargin: 10

        Text {
            id: name
            text: "From " + name
            font.pointSize: 50
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


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
