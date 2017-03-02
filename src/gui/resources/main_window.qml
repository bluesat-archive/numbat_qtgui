import QtQuick 2.0
import QtQuick.Window 2.2
import bluesat.owr 1.0
import bluesat.owr.singleton 1.0

Window {
    id: main_window
    width: 800
    height: 800
    property alias cmd_vel_display: cmd_vel_display
    title: "BLUEsat OWR"
    visible: true
    minimumHeight: 600
    minimumWidth: 600
    
    Image {
        id: logo
        source: "/images/bluesatLogo.png"
        width: 244
        height: 116
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }


    Item {
        id: video_pane
        x: 198
        width: 245
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: logo.bottom
        anchors.topMargin: 83
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 351
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
    Item {
        id: cmd_vel_display

        anchors.right: video_pane.right
        anchors.rightMargin: 0
        anchors.left: video_pane.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: video_pane.bottom
        anchors.topMargin: 10

        Rectangle {
            id: cmd_vel_border
            border.color: "#0025df"
            anchors.fill: parent
            border.width: 3
        }

        Canvas {
            id: pos

            property double inputX: RoverCmdState.drive_x
            property double inputY: RoverCmdState.drive_y
            property double scale: 50
            clip: true
            anchors.topMargin: 29
            anchors.fill: parent

            Component.onCompleted: {
                RoverCmdState.onCmd_vel_changed.connect(requestPaint)
            }

            onPaint: {
                console.log(RoverCmdState.drive_x);
                var context = getContext("2d");

                //clear the canvas
                context.beginPath();
                context.clearRect(0,0,width,height);
                context.fill();

                //draw the circle
                context.beginPath();
                context.strokeStyle = "black";
                context.moveTo(width/2+scale, height/2);
                context.arc(width/2, height/2, scale, 0, 2*Math.PI, true);
                context.stroke();

                //draw the line
                context.beginPath();
                context.lineWidth = 2;
                context.moveTo(width/2, height/2);
                context.strokeStyle = "red";
                context.lineTo((width/2) + (inputX * scale), (height/2) + (inputY * scale));
                context.stroke();
            }

        }

        Text {
            id: text1
            x: 8
            y: 9
            text: qsTr("Rover Driver Direction/Velocity")
            font.pixelSize: 14
        }

    }

}
