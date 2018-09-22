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
        anchors.right: parent.left
        anchors.rightMargin: -200
        anchors.left: parent.left
        anchors.leftMargin: 0
        z: 100
        anchors.bottom: camera_switching_container.top
        anchors.bottomMargin: -54
        anchors.topMargin: 0
        opacity: 0.5
        anchors.top: parent.top
        fillMode: Image.PreserveAspectFit
    }

    Item {
        id: video_pane
        z: -1
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        ROSVideoComponent {
            // @disable-check M16
            objectName: "videoStream"
            id: videoStream
            // @disable-check M16
            fillColor: qsTr("#000000")
            // @disable-check M16
            anchors.fill: parent
            // @disable-check M16
            anchors.bottom: parent.bottom
            // @disable-check M16
            anchors.top: parent.top
            // @disable-check M16
            anchors.left: parent.left
            // @disable-check M16
            anchors.right: parent.right
            // @disable-check M16
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
        z: 4
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.right
        anchors.leftMargin: -172
        anchors.bottom: parent.top
        anchors.bottomMargin: -100
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

            // @disable-check M16
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

            ROSJoystickListener {
                // @disable-check M16
                objectName: "bot_joystick"
                // @disable-check M16
                topic: "/joy"
                // @disable-check M16
                onButton_down: {
                    var start_number = camera_switching.camera_number;

                    // handle the case where no camera is selected
                    if(start_number < 0) {
                        start_number = 0;
                    }

                    if(button === 4) { // Left Buffer
                        camera_switching.camera_number = (start_number - 1) % 8;
                    } else if(button === 5) { // Right Buffer
                        camera_switching.camera_number = (start_number + 1) % 8;
                    }
                }
            }
        }
    }

    DriveModeWidget {
        id: drive_mode
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: signal_strength_container.left
        anchors.leftMargin: 0
        anchors.top: signal_strength_container.bottom
        anchors.topMargin: 10
    }

    VoltageMeterWidget {
        id: voltage_meter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: drive_mode.left
        anchors.leftMargin: 0
        anchors.top: drive_mode.bottom
        anchors.topMargin: 30
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

    /*Item {
        id: usb_container
        z: 5
        x : 40
        y : 40
        ROSUsbReset {
            // @disable-check M16
            objectName: "signal_strength"
            id: usb
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
            topic: qsTr("/rover/usb")
        }

    }*/
}
