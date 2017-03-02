import QtQuick 2.0
import QtQuick.Window 2.2
import bluesat.owr 1.0
import bluesat.owr.singleton 1.0

Item {
    id: cmd_vel_display
    
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
            context.lineTo((width/2) - (inputX * scale), (height/2) - (inputY * scale));
            context.stroke();
        }
        
    }
    
    Text {
        id: text1
        x: 8
        y: 9
        text: qsTr("Rover Driver Direction/Velocity")
        font.underline: true
        font.pixelSize: 14
    }
    
}
