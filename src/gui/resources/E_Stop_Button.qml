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

    onClicked:
    {
        E_Stop_Button.press = true;
    }

}
