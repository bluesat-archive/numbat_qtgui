import QtQuick 2.0
import QtQuick.Window 2.2
import bluesat.owr 1.0

Window {
    id: main_window
    width: 800
    height: 600
    title: "BLUEsat OWR"
    visible: true
    minimumHeight: 600
    minimumWidth: 450

    Image {
        id: logo
        source: "/images/bluesatLogo.png"
        width: 244
        height: 116
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }


    ROSVideoComponent {
        // @disable-check M16
        objectName: "videoStream"
        id: videoStream
        // @disable-check M16
        anchors.top: parent.top
        // @disable-check M16
        anchors.horizontalCenter: parent.horizontalCenter
        // @disable-check M16
        width: 640
        // @disable-check M16
        height: 480
        // @disable-check M16
        topic: topic.text
    }

        Stopwatch {
            // @disable-check M16
            objectName: "timerDisplay"
            id: timerDisplay
            // @disable-check M16
            anchors.bottom: videoStream.bottom
            // @disable-check M16
            anchors.bottomMargin: 5
            // @disable-check M16
            anchors.right: videoStream.right
            // @disable-check M16
            anchors.rightMargin: 5
            // @disable-check M16
            focus:true;
/*
            // @disable-check M16
            anchors.bottom: parent.bottom
            // @disable-check M16
            anchors.bottomMargin: 0
            // @disable-check M16
            anchors.top: logo.bottom
            // @disable-check M16
            anchors.topMargin: 10
*/
            // @disable-check M16
            width:145
            // @disable-check M16
            height: 55

        }


    TextInput {
        id: topic
        x: 72
        y: 500
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
}
