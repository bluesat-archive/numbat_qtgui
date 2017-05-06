import QtQuick 2.0
import QtQuick.Window 2.2
import bluesat.owr 1.0

Window {
    id: main_window
    width: 400
    height: 400
    title: "BLUEsat OWR"
    visible: true
    minimumHeight: 300
    minimumWidth: 300
    
    Image {
        id: logo
        source: "/images/bluesatLogo.png"
        width: 244
        height: 116
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

        Stopwatch {
            // @disable-check M16
            objectName: "timerDisplay"
            id: timerDisplay

            // @disable-check M16
            anchors.bottom: parent.bottom
            // @disable-check M16
            anchors.bottomMargin: 0
            // @disable-check M16
            anchors.top: logo.bottom
            // @disable-check M16
            anchors.topMargin: 10
            // @disable-check M16
            width: 244
            // @disable-check M16
            height: 116

        }
    }

/*
    Item {
        id: video_pane
        x: 198
        width: 245
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: logo.bottom
        anchors.topMargin: 83
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        ROSVideoComponent {
            // @disable-check M16
            objectName: "videoStream"
            id: videoStream
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
            topic: topic.text
        }
    }

    TextInput {
        id: topic
        x: 40
        y: 335
        width: 80
        height: 20
        text: qsTr("/cam0")
        font.pixelSize: 12
    }
*/
