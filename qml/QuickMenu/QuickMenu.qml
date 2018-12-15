import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Drawer {
    id: quickMenu
    width: 800
    height: 300
    edge: Qt.TopEdge

    property real batterySOC: 1.0

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 5
        Rectangle {
            id: leftBox
            width: parent.width/3
            color: "#2926f4"
            Layout.fillHeight: true
            radius: 20

            Text {
                id: leftBox_timeText
                width: parent.width
                height: parent.height / 4
                text: qsTr("12:00")
                fontSizeMode: Text.Fit
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 80
                color: "white"
            }

            Text {
                id: leftBox_dateText
                anchors.top: leftBox_timeText.bottom
                width: parent.width
                height: parent.height / 6
                text: qsTr("Thu, Aug 20")
                fontSizeMode: Text.Fit
                font.pixelSize: 40
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white"
            }

            Rectangle {
                width: batteryBody.width/2
                height: 10
                anchors.bottom: batteryBody.top
                anchors.horizontalCenter: batteryBody.horizontalCenter
                color: batteryBody.color
            }

            Rectangle {
                id: batteryBody
                anchors.top: leftBox_dateText.bottom
                anchors.topMargin: 40
                anchors.left: parent.left
                anchors.leftMargin: 40
                height: 100
                width: 50
                color: "grey"
                Rectangle {
                    id: batteryCapacityIndicator
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width * 0.85
                    height: parent.height * 0.9 * batterySOC
                    color: "green"

                    states: [ State {
                        name: "lowBattery"
                        PropertyChanges {
                            target: batteryCapacityIndicator
                            color: "red"
                        }
                    }]
                }
            }
            Text{
                id: remainingBatteryLifeText
                anchors.left: batteryBody.right
                anchors.leftMargin: 15
                anchors.verticalCenter: batteryBody.verticalCenter
                text: "5:00"
                font.pixelSize: 50
                color: "white"
            }
        }
        SwipeView {
            id: menuSwitch
            width: parent.width - leftBox.width
            clip: true
            Layout.fillHeight: true

            Page {
                id: recentMessages
                Rectangle {
                    anchors.fill: parent
                    color: "#4b4b4b"
                    radius: 20
                    Text {
                        id: recentMessages_title
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.leftMargin: 15
                        anchors.topMargin: 15
                        color: "white"
                        font.pixelSize: 40
                        text: qsTr("Latest Messages")
                        fontSizeMode: Text.VerticalFit
                    }

                    ScrollView {
                        id: scrollView
                        anchors.top: recentMessages_title.bottom
                        anchors.bottom: parent.bottom
                        width: parent.width
                    }
                }
                background: null
            }
            Page {
                id: recentPhotos
                Rectangle {
                    anchors.fill: parent
                    color: "#4b4b4b"
                    radius: 20

                    Text {
                        id: recentPhotos_title
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.leftMargin: 15
                        anchors.topMargin: 15
                        color: "white"
                        font.pixelSize: 40
                        text: qsTr("Latest Photos")
                        fontSizeMode: Text.VerticalFit
                    }
                }
                background: null
            }
            background: null
        }
    }
    background: null

    Connections{
        target: gestureManager
        onToDown: {
            quickMenu.open()
            quickMenu.focus = false
        }
        onToUp: {
            quickMenu.close()
            swipeView.focus = true
        }
        onToRight: {
            if(menuSwitch.currentIndex != 0 && quickMenu.opened) menuSwitch.currentIndex -= 1
        }
        onToLeft: if(menuSwitch.currentIndex + 1 != menuSwitch.count && quickMenu.opened) menuSwitch.currentIndex += 1
    }
}

