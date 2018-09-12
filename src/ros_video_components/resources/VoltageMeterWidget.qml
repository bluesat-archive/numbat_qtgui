import QtQuick 2.0
import bluesat.owr 1.0

Item {
    id: voltage_meter_widget
    ROSVoltageMeter {
        objectName: "voltage_meter"
        id: voltageMeter
        topic: "/rover/volt"
        // @disable-check M16`
        anchors.bottom: parent.bottom
        // @disable-check M16
        anchors.bottomMargin: 0
        // @disable-check M16
        anchors.top: parent.top
        // @disable-check M16
        anchors.left: parent.left
        // @disable-check M16
        anchors.right: parent.right
    }
    Text {
        id: voltageValue
        color: "#d23a00"
        text: voltageMeter.volt_value
        fontSizeMode: Text.HorizontalFit
        clip: false
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.leftMargin: 40
        horizontalAlignment: Text.AlignLeft
        font.pointSize: 10
        font.bold: true
    }
    Text {
        id: voltageValueText
        text: qsTr("Volt:")
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
