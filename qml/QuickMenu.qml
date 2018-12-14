import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Drawer {
    id: quickMenu
    width: 800
    height: 300
    edge: Qt.TopEdge

    RowLayout {
        anchors.fill: parent
        spacing: 5
        Rectangle {
            id: leftBox
            width: parent.width/3
            color: "#2926f4"
            Layout.fillHeight: true

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
                        anchors.top: title.bottom
                        anchors.bottom: parent.bottom
                        width: parent.width
                    }
                }
            }
            Page {
                id: recentPhotos
                Rectangle {
                    anchors.fill: parent
                    color: "#4b4b4b"

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
            }
        }
    }
    background: null

    Connections{
        target: gestureManager
        onToDown: {
            quickMenu.open()
            quickMenu.focus = false
//                swipeView.focus = false
        }
        onToUp: {
            quickMenu.close()
            swipeView.focus = true
        }
        onToRight: {
            if(menuSwitch.currentIndex + 1 != menuSwitch.count && quickMenu.opened) menuSwitch.currentIndex += 1
        }
        onToLeft: if(menuSwitch.currentIndex != 0 && quickMenu.opened) menuSwitch.currentIndex -= 1
    }
}

