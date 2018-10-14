import QtQuick 2.9
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 480
    title: qsTr("Tabs")

    Popup {
        id: popup
//        parent: parent.contentItem
        enabled: true
        visible: false
        focus: true
        modal: true
        opacity: .9
        transformOrigin: Popup.Center
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: parent.width * 1
        height: parent.height * 1
        enter: Transition{
            ParallelAnimation {
                NumberAnimation { target: popup; property: "y"; from: -height; duration: 500;
                    to: Math.round((root.height - height) / 2)}
                NumberAnimation { target: popup; property: "opacity"; from: 0.0; to: 0.9; duration: 500 }
            }
        }
        exit: Transition {


        }

        property string nameText
        property string bodyText

        contentItem: Item{
            anchors.fill: parent
            Rectangle {
                id: bodyBox
                x: Math.round((parent.width - width) / 2)
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                width: parent.width *.8
                height: parent.height * .7
                color: "#c4c4c4"
                radius: 30
                Text {
                    id: body
                    text: popup.bodyText
                    clip: true
                    wrapMode: Text.WordWrap
                    fontSizeMode: Text.Fit
                    font.pointSize: 80
                    minimumPointSize: 50
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    width: parent.width * .93
                    height: parent.height * .93
                }
            }

            Rectangle {
                id: nameBox
                width: bodyBox.width
//                height: parent.height * .2
                color: "#2958ff"
                anchors.left: bodyBox.left
                anchors.bottom: bodyBox.top
                anchors.top: parent.top
                anchors.topMargin: 30
                radius: 30

                Text {
                    id: name
                    text: "From " + popup.nameText
                    font.pointSize: 100
                    minimumPointSize: 50
                    color: "#ffffff"
                    fontSizeMode: Text.Fit
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    width: parent.width * .93
                    height: parent.height * .85
                }
            }
        }
        background: Item {
//            anchors.fill: root
            ShaderEffectSource {
                id: effectSource
                sourceItem: swipeView
                anchors.fill: parent
                sourceRect: Qt.rect(popup.x,popup.y,popup.width,popup.height)
            }
            FastBlur{
                id: blur
                anchors.fill: effectSource
                source: effectSource
                radius: 100
                visible: false
            }
        }

    }
//    FastBlur{
//        id: blur
//        visible: false
//        source: homePage
//        anchors.fill: homePage
//        radius: 100
//    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
//        Repeater{

//        }

        Page1Form {
            id: homePage
        }

        Page2Form {

        }
    }
    Connections {
        target: swipeManager
        onToUp: {
            if(popup.opened) {
                upExit.start()
//                popup.close()
            }
        }

        onToRight: {

            if(swipeView.currentIndex + 1 != swipeView.count) swipeView.currentIndex += 1
        }
        onToLeft: if(swipeView.currentIndex != 0) swipeView.currentIndex -= 1
    }

    ParallelAnimation {
        id: upExit
        running: false
        onStopped: popup.close()
        NumberAnimation { target: popup; property: "y"; duration: 500;
            from: Math.round((root.height - height) / 2); to: -height }
        NumberAnimation { target: popup; property: "opacity"; from: 0.9; to: 0.0; duration: 500 }
    }

    Connections{
        target: smsManager
        onLaunchMessagePopup:
        {
            popup.nameText = smsManager.name
            popup.bodyText = smsManager.body
            popup.open()
            blur.visible = true
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        height: 50
        TabButton {
            text: qsTr("Page 1")
        }
        TabButton {
            text: qsTr("Page 2")
        }
    }
}
