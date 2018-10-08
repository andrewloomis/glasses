import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 480
    height: 320

    header: Label {
        text: qsTr("Page 2")
        font.pixelSize: 45
        padding: 10
    }

    Label {
        text: qsTr("You are on Page 2.")
        anchors.verticalCenterOffset: -42
        anchors.horizontalCenterOffset: 1
        font.pointSize: 41
        anchors.centerIn: parent
    }
}
