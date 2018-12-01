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
        width: 100
        height: 30
        x: 20
        y: 20
        visible: true
        property bool hold: false

        onClicked:
          {

              if (!hold)
              {
                  hold = true;
                  e_stop_button_background.color = "#c91f1f";
                  e_stop_button_text.font.pointSize = 16;
              }
              else
              {
                  hold = false;
                  e_stop_button_background.color = "green";
                   e_stop_button_text.font.pointSize = 18;
              }

              E_Stop_Joints_Widget.press = hold;
          }

          Rectangle
          {
              id: e_stop_button_background
                color: "green"
              //border.width: 3
              //border.color: "black"
              anchors.fill: parent

              Text
              {

                  id: e_stop_button_text
                  text: "E-Stop"
                  font.pointSize: 18
                  style: Text.Sunken
                  font.bold: true
                  font.family: "Courier"
                  anchors.fill: parent
                  horizontalAlignment: Text.AlignHCenter
                  verticalAlignment: Text.AlignVCenter
                  fontSizeMode: Text.FixedSize
                  color: "white"

              }

          }


    }
Component.onCompleted: {
    console.log("e_stop_joints_widget Started Successfully")
        //E_Stop_Joints_Widget.press = false;
    }
}

