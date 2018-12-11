import QtQuick 2.9
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 480
    title: qsTr("Tabs")
    
    KeyboardInput{
        LockScreen{
            visible: true
            focus: true
        }

//        MessagePopup{
//            id: popup
//        }

//        ParallelAnimation {
//            id: upExit
//            running: false
//            onStopped: popup.close()
//            NumberAnimation { target: popup; property: "y"; duration: 500;
//                from: Math.round((root.height - height) / 2); to: -height }
//            NumberAnimation { target: popup; property: "opacity"; from: 0.9; to: 0.0; duration: 500 }
//        }
    
        SwipeView {
            id: swipeView
//            focus: false
            visible: false
            anchors.fill: parent
            currentIndex: tabBar.currentIndex

            Page1Form {
                id: homePage
            }

            Page2Form {

            }
        }
    
        Connections {
            target: gestureManager
//            onToUp: {
//                if(popup.opened) {
//                    upExit.start()
//                }
//            }
            onToRight: {
                if(swipeView.currentIndex + 1 != swipeView.count) swipeView.currentIndex += 1
            }
            onToLeft: if(swipeView.currentIndex != 0) swipeView.currentIndex -= 1
        }
//        Connections{
//            target: smsManager
//            onLaunchMessagePopup:
//            {
//                popup.nameText = smsManager.name
//                popup.bodyText = smsManager.body
//                popup.open()
//                blur.visible = true
//            }
//        }
    }

    footer: TabBar {
        id: tabBar
        visible: false
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
