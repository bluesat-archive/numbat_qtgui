import QtQuick 2.0
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

    //Battery indicator
    Rectangle {
        id: battery_indicator
        property var charge: 33
        height: 15
        width: charge
        color: "white"
        x : 20
        y : 20
        border.width: 1
        focus: true
        Keys.enabled: true
        Keys.forwardTo: [rect]
        Keys.onEscapePressed: {
            Qt.quit;
        }
        Rectangle {
            width: 1
            height: 15
            x : battery_indicator.charge/3
            color: "black"
            border.width: 0
            z: 1
        }
        Rectangle {
            width: 1
            height: 15
            x : (battery_indicator.charge/3)*2
            color: "black"
            border.width: 0
            z: 1
        }
        Rectangle {
            x: battery_indicator.charge
            y: 4
            height:7
            width: 3
            color: "black"
        }
        Rectangle {
            id : rect
            height: 15
            width: battery_indicator.charge
            //color: "green"
            border.width: 1
            Keys.enabled: true
            Keys.onPressed: {
                switch(event.key)
                {
                case Qt.Key_Left: //when left is pressed, battery indicator decreases by 5
                        width -= (battery_indicator.charge)/10
                        break;
                case Qt.Key_Right: //when right is pressed, battery indicator increases by 5
                       width += (battery_indicator.charge)/10
                        break;
                }
            }
            Text {
                x: battery_indicator.charge + 5
                text: "%d", Math.round((rect.width/battery_indicator.charge)*100)
            }
            color: "green"

        }
}
    Image {
        id: logo
        source: "/images/bluesatLogo.png"
        width: 244
        height: 116
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

/*
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
*/
    Item {
        id: video_pane
        x: 198
        width: 800
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
        anchors.bottom: video_pane.bottom
        anchors.bottomMargin: 2
        anchors.left: video_pane.left
        //x: 72
        //y: 500
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
    Stopwatch {
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
            width: 160
            // @disable-check M16
            height: 80

    }
}
