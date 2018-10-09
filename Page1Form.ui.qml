import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 480
    height: 320
    Image {
        id: image
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectCrop
        source: "saturn.jpg"
    }
    Label {
        id: timeLabel
        x: 76
        y: 80
        width: 328
        height: 161
        text: "NaN"
        font.pointSize: 100
        color: "#ffffff"
    }
    Connections {
        target: timeManager
        onUpdateUiTime: {
            timeLabel.text = timeManager.dayOfWeek
        }
    }
}
