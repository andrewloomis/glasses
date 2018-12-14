import QtQuick 2.0

Item {
    id: lockScreen
    width: 800
    height: 480
    Rectangle {
        anchors.fill: parent
        color: "#ffffff"

        Image {
            id: fingerprintImage
            x: parent.width / 16
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width / 2
            height: parent.width / 2
            fillMode: Image.PreserveAspectFit
            source: "fingerprint.png"
        }
        Item {
            x: parent.width / 2
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width / 2
            height: parent.height / 2
            Text {
                id: timeText
                width: parent.width
                height: parent.height / 2
                text: qsTr("12:00")
                fontSizeMode: Text.Fit
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 80
            }

            Text {
                id: dateText
                anchors.top: timeText.bottom
                width: parent.width
                height: parent.height / 6
                text: qsTr("Thu, Aug 20")
                fontSizeMode: Text.Fit
                font.pixelSize: 40
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Connections {
        target: authenticationManager
        onUnlock: if(activeFocus) {
            fingerprintImage.source = "fingerprint_highlighted.png"
            unlockTimer.start()
            fadeOut.start()
            tabBarFadeIn.start()
            swipeView.focus = true
        }
    }

    NumberAnimation {
        id: fadeOut
        target: lockScreen
        property: "opacity"
        duration: 2000
        easing.type: Easing.InOutQuad
        from: 1
        to: 0
    }

    // Emulated Unlock (only for testing)
    Timer {
        id: unlockTimer
        interval: 2000
        repeat: false
        onTriggered: {
            lockScreen.focus = false
        }
    }
}
