import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import bluesat.owr.singleton 1.0

Button {

    id: e_stop_button
    width: 100
    height: 100
    visible: true

    property bool hold: false

    onClicked:
    {

        if (!hold)
        {
            hold = true;
            e_stop_button_background.color = "#871d1d";
            e_stop_button_background.border.width = 7;
            //e_stop_button_background.border.color = "yellow";

            e_stop_button_text.font.pointSize = 16;
        }
        else
        {
            hold = false;
            e_stop_button_background.color = "#c91f1f";
            e_stop_button_background.border.width = 3;
            //e_stop_button_background.border.color = "white";

            e_stop_button_text.font.pointSize = 18;
        }

        E_Stop_Button.press = hold;
    }

    Rectangle
    {
        id: e_stop_button_background
        color: "#c91f1f"
        border.width: 3
        border.color: "yellow"
        anchors.fill: parent

        Text
        {

            id: e_stop_button_text
            text: "E-STOP"
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
