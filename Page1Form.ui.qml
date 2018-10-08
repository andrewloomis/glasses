import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 480
    height: 320

    header: Label {
        text: qsTr("Page 1")
        font.pixelSize: 44
        padding: 10
    }

    Label {
        width: 464
        height: 173
        text: qsTr("You are on Page 1.")
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 17
        font.pointSize: 36
        fontSizeMode: Text.HorizontalFit
        anchors.centerIn: parent
    }
}
