import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 480
    height: 320
    title: qsTr("Tabs")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
//        Repeater{

//        }

        Page1Form {
        }

        Page2Form {
        }
    }
    Connections {
        target: manager
        onToRight: if(swipeView.currentIndex + 1 != swipeView.count) swipeView.currentIndex += 1
        onToLeft: if(swipeView.currentIndex != 0) swipeView.currentIndex -= 1
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
