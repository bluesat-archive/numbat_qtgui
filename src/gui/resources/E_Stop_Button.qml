import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import bluesat.owr.singleton 1.0

Button {

    id: e_stop_button
    width: 100
    height: 100
    visible:true
    text: qsTr("!!STOP!!")

    property var hold: false

    onClicked:
    {

        if (!hold)
        {
            E_Stop_Button.hold = true;
            hold = true;
            text = "Click to release"
        }
        else
        {
            E_Stop_Button.hold = false;
            hold = false;
            text = "!!STOP!!";
        }

        E_Stop_Button.press = true;
    }

}
