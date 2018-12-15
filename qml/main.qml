import QtQuick 2.9
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import "misc"
import "MainPages"
import "QuickMenu"
import "LockScreen"

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 480
    title: qsTr("Tabs")
    onActiveFocusItemChanged: print("activeFocusItem", activeFocusItem)

    property var pageList: ["Messages", "Home", "Camera", "Library"]

    KeyboardInput {
//        id: keyboardScope
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
        QuickMenu {
            id: quickMenu
        }

        SwipeView {
            id: swipeView
            focus: false
            visible: true
            anchors.fill: parent
            currentIndex: 1

            MessagesPage {

            }

            HomePage {

            }

            CameraPage {

            }

            LibraryPage {

            }
            Connections {
                target: gestureManager
                onToRight: {
                    if(swipeView.currentIndex + 1 != swipeView.count && swipeView.activeFocus && !quickMenu.opened) swipeView.currentIndex += 1
                }
                onToLeft: if(swipeView.currentIndex != 0 && swipeView.activeFocus && !quickMenu.opened) swipeView.currentIndex -= 1
            }
        }
        LockScreen {
            visible: true
            focus: true
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
        visible: true
        opacity: 0
        currentIndex: swipeView.currentIndex
        height: 50
        TabButton {
            text: pageList[0]
        }
        TabButton {
            text: pageList[1]
        }
        TabButton {
            text: pageList[2]
        }
        TabButton {
            text: pageList[3]
        }

        NumberAnimation {
            id: tabBarFadeIn
            target: tabBar
            property: "opacity"
            duration: 1000
            easing.type: Easing.InOutQuad
            from: 0
            to: 1
        }
    }

}
