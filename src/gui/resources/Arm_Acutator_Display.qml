import QtQuick 2.0
import QtQuick.Window 2.2
import bluesat.owr 1.0
import bluesat.owr.singleton 1.0

Item {
    id: arm_acutator_display
    property string extension_state: qsTr("Stop")
    property string name_text: qsTr("Actuator")
    width: 600
    height: 200

    Rectangle {
        id: arm_border
        border.color: "#0025df"
        anchors.fill: parent
        border.width: 3
    }

    Image {
        id: actuator_image
        width: 224
        height: 86
        anchors.top: name_text_label.bottom
        anchors.topMargin: 10
        sourceSize.height: 172
        sourceSize.width: 448
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        fillMode: Image.PreserveAspectFit
        source: "qrc:/images/actuator.JPG"
    }
    
    Text {
        id: extension_state_text
        text: parent.extension_state
        anchors.right: parent.right
        anchors.rightMargin: 10
        verticalAlignment: Text.AlignVCenter
        anchors.bottom: actuator_image.bottom
        anchors.bottomMargin: 0
        anchors.top: actuator_image.top
        anchors.topMargin: 0
        anchors.left: actuator_image.right
        anchors.leftMargin: 20
        font.pixelSize: 14
    }

    Text {
        id: name_text_label
        text: parent.name_text
        font.underline: true
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.verticalCenter
        anchors.bottomMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: actuator_image.left
        anchors.leftMargin: 0
        font.pixelSize: 14
    }
    
}
