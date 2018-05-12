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


    // Left-over code, needs cleanup
    /*
    Rectangle{
        //draw a rectangle on the surface at x=40, y=50
        //define its height and width
        //no color filled inside
        x:40
        y:50
        width:100
        height:20


        //set this rectangle focus on key strike
        //enable processing of key press
        //once key pressed, send the info to camera_switch_button
        focus: true;
        Keys.enabled: true;
        Keys.forwardTo: [camera_switch_button];

        Rectangle{
            //basic info
            x:40
            y:50
            width:100
            height:20
            id:camera_switch_button

            //color is red
            color:"red"

            Keys.onPressed: {
                        switch(event.key){
                        //if g is pressed
                        //change color to green
                        case Qt.Key_G:
                            color = "green";
                            break;

                        //if r is pressed
                        //change color to red
                        case Qt.Key_R:
                            color = "red";
                            break;

                        default:
                            return;
                        }
                        event.accepted = true;
            }
        }

    }
    */

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
