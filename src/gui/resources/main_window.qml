import QtQuick 2.5
import QtQuick.Window 2.2
import bluesat.owr 1.0



Window {
    id: main_window
    width: 800
    height: 800
    title: "BLUEsat OWR"
    visible: true
    minimumHeight: 600
    minimumWidth: 600

    Image {
        id: logo
        source: "/images/bluesatLogo.png"
        width: 244
        height: 116
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Item {
        id: video_pane
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: logo.bottom
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        ROSVideoComponent {
            objectName: "videoStream"
            id: videoStream
            fillColor: qsTr("#000000")
            anchors.fill: parent
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            topic: camera_switching.camera_topic
            Text {
                id: text1
                text: videoStream.topic
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                font.pixelSize: 12
            }
        }

    }

    Item {
        id: signal_strength_container
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: logo.right
        anchors.leftMargin: 76
        //anchors.bottom: videoStream.top
        anchors.bottom: video_pane.top
        anchors.bottomMargin: 90
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
    Item{
        id: camera_switching_container
        width: 50
        height: 660
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.rightMargin: -800
        anchors.bottom: parent.top
        anchors.right: parent.left
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottomMargin: -800

        ROSCameraSwitching {
            // @disable-check M16
            objectName: "camera_switching"
            id: camera_switching
            // @disable-check M16
            anchors.bottom: parent.bottom
            // @disable-check M16
            anchors.bottomMargin: 0
            // @disable-check M16
            anchors.top: parent.top
            // @disable-check M16
            anchors.topMargin: 0
            // @disable-check M16
            anchors.left: parent.left
            // @disable-check M16
            anchors.right: parent.right
            // @disable-check M16
            topic: qsTr("/owr/control/availableFeeds")

            focus: true

            Shortcut {
                sequence: "0"
                onActivated: camera_switching.camera_number = 0
            }
            Shortcut {
                sequence: "1"
                onActivated: camera_switching.camera_number = 1
            }
            Shortcut {
                sequence: "2"
                onActivated: camera_switching.camera_number = 2
            }
            Shortcut {
                sequence: "3"
                onActivated: camera_switching.camera_number = 3
            }
            Shortcut {
                sequence: "4"
                onActivated: camera_switching.camera_number = 4
            }
            Shortcut {
                sequence: "5"
                onActivated: camera_switching.camera_number = 5
            }
            Shortcut {
                sequence: "6"
                onActivated: camera_switching.camera_number = 6
            }
            Shortcut {
                sequence: "7"
                onActivated: camera_switching.camera_number = 7
            }
        }
    }

    ROSTimer {
        // @disable-check M16
        objectName: "timerDisplay"
        id: timerDisplay
        // @disable-check M16
        anchors.bottom: video_pane.bottom
        // @disable-check M16
        anchors.bottomMargin: 5
        // @disable-check M16
        anchors.right: video_pane.right
        // @disable-check M16
        anchors.rightMargin: 5
        // @disable-check M16
        focus:true;
        // @disable-check M16
        width: 160
        // @disable-check M16
        height: 80

    }
}
