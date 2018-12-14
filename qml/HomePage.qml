import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    id: timePage
    width: 800
    height: 480

    Image {
        id: image
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectCrop
        source: "saturn.jpg"
    }
    Label {
        id: timeLabel
        width: 486
        height: 242
        text: "12:00"
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: parent.height / 2
        color: "#ffffff"
    }
    Connections {
        target: timeManager
        onUpdateUiTime: {
            timeLabel.text = timeManager.timeString
            dateLabel.text = timeManager.dateString
        }
    }

    Label {
        id: dateLabel
        anchors.horizontalCenter: parent.horizontalCenter
        width: 328
        height: 90
        color: "#ffffff"
        text: "Thu, Aug 20"
        anchors.horizontalCenterOffset: 0
        anchors.top: parent.top
        anchors.topMargin: 20
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: parent.height / 5
    }
}
