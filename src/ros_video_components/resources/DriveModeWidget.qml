import QtQuick 2.0
import bluesat.owr 1.0

Item {
    id: drive_mode_widget

    ROSDriveMode {
        objectName: "drive_mode"
        id: driveMode
        topic: "/cmd_vel/mode"

    }

    Text {
        id: driveModeText
        color: "#d23a00"
        text: driveMode.mode
        fontSizeMode: Text.HorizontalFit
        clip: false
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.leftMargin: 15
        horizontalAlignment: Text.AlignLeft
        font.pointSize: 10
        font.bold: true
    }

    Text {
        id: driveText
        text: qsTr("Drive:")
        fontSizeMode: Text.HorizontalFit
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        color: "#d23a00"
        horizontalAlignment: Text.AlignLeft
        font.pointSize: 10
        font.bold: true
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 0
    }
}
