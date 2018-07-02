import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import bluesat.owr.singleton 1.0
import QtQuick 2.0

Item {
    id: e_stop_joints_widget
    visible:true
    width: 600
    height: 600

    Button {
        id: button
        x: 196
        y: 356
        text: qsTr("Button")
        onClicked: {
                button.x += 10
                E_Stop_Joints_Widget.press = true;
            //backgroundColourButton.setStyleSheet("background-color: red");
            //backgroundColourButton.qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #0d5ca6, stop: 1 #2198c0);
            //button.backgroundColour.setStyleSheet("background-color: red");
            }
    }
Component.onCompleted: {
    console.log("e_stop_joints_widget Started Successfully")
        E_Stop_Joints_Widget.press = false;
    }
}

