import QtQuick 2.0
import QtQuick.Window 2.2
import bluesat.owr 1.0

Window {
    id: main_window
    width: 800
    height: 600
    title: "BLUEsat OWR"
    visible: true
    minimumHeight: 720
    minimumWidth: 540

    Image {
        id: logo
        source: "/images/bluesatLogo.png"
        width: 244
        height: 116
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }


    ROSVideoComponent {
        // @disable-check M16
        objectName: "videoStream"
        id: videoStream
        // @disable-check M16
        anchors.top: logo.bottom
        // @disable-check M16
        anchors.horizontalCenter: parent.horizontalCenter
        // @disable-check M16
        width: 640
        // @disable-check M16
        height: 480
        // @disable-check M16
        topic: topic.text
    }

    TextInput {
        id: topic
        anchors.top: videoStream.bottom
        anchors.topMargin: 2
        anchors.left: videoStream.left
        width: 80
        height: 20
        text: qsTr("/cam0")
        font.pixelSize: 12
    }


    Item {
        id: signal_strength_container
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: logo.right
        anchors.leftMargin: 103
        anchors.bottom: videoStream.top
        anchors.bottomMargin: 100
        ROSSignalStrength {
            // @disable-check M16
            objectName: "signal_strength"
            id: signal_strength
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
            // @disable-check M16
            topic: qsTr("/rover/signal")
        }
    }

    ROSCoordBearing {
        // @disable-check M16
        objectName: "coord_bearing"
        id: coord_bearing
        // @disable-check M16
        anchors.bottom: videoStream.bottom
        // @disable-check M16
        anchors.bottomMargin: 5
        // @disable-check M16
        anchors.left: videoStream.left
        // @disable-check M16
        anchors.leftMargin: 10
        // @disable-check M16
        width: 145
        // @disable-check M16
        height: 65

    }
}
