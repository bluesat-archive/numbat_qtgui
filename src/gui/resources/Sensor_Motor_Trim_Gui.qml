import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
//import bluesat.owr 1.0
import bluesat.owr.singleton 1.0

//Gui widget for trimming sensors/motor values
//Fixed size of 600x250p

Item {
    id: sensor_motor_trim
    visible:true
    width: 600
    height: 250

    Component.onCompleted: {
        console.log("Sensor/Motor Trim started")
    }

    //Title
    Text {
        id: title
        x: 146
        y: 38
        text: qsTr("Trim Sensors/Joints")
        font.pixelSize: 32
    }

    //Button for submitting
    Button {
        id: submit_button
        x: 396
        y: 161
        height: 20
        text: qsTr("Submit")
        onClicked: {
            if (value_text.acceptableInput) {
                Sensor_Motor_Trim.value = value_text.text*1
                Sensor_Motor_Trim.index = component_list.currentIndex
                Sensor_Motor_Trim.press = 1
                component_list.model.get(component_list.currentIndex).normal = value_text.text*1
            }
        }
    }

    //Warning message for out of bounds input
    Text {
        id: value_warning
        x: 165
        y: 82
        width: 270
        height: 20
        color: "#ff0000"
        text: qsTr(
                   "Please enter a value between %1 and %2"
        ).arg(
                   component_list.model.get(component_list.currentIndex).minimum
        ).arg(
                   component_list.model.get(component_list.currentIndex).maximum
        )
        visible: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
    }

    //Component list - for choosing what element to edit
    ComboBox {
        id: component_list
        x: 101
        y: 115
        width: 200
        height: 20
        editable: false
        model: ListModel {
            id: cbItems
            ListElement {
                minimum: -250
                normal: 0
                maximum: 250
                text: "Front Left Wheel"
            }
            ListElement {
                minimum: -250
                normal: 0
                maximum: 250
                text: "Front Right Wheel"
            }
            ListElement {
                minimum: -250
                normal: 0
                maximum: 250
                text: "Back Left Wheel"
            }
            ListElement {
                minimum: -250
                normal: 0
                maximum: 250
                text: "Back Right Wheel"
            }
            ListElement {
                minimum: -500
                normal: 0
                maximum: 500
                text: "Front Left Swerve"
            }
            ListElement {
                minimum: -500
                normal: 0
                maximum: 500
                text: "Front Right Swerve"
            }
            ListElement {
                minimum: -500
                normal: 0
                maximum: 500
                text: "Back Left Swerve"
            }
            ListElement {
                minimum: -500
                normal: 0
                maximum: 500
                text: "Back Right Swerve"
            }
            ListElement {
                minimum: -300
                normal: 0
                maximum: 300
                text: "Arm Base Rotate"
            }
            ListElement {
                minimum: -500
                normal: 0
                maximum: 500
                text: "Arm Upper Act."
            }
            ListElement {
                minimum: -500
                normal: 0
                maximum: 500
                text: "Arm Lower Act."
            }
        }

        onCurrentTextChanged: {
            value_text.text = qsTr("%1").arg(this.model.get(this.currentIndex).normal)
            if (value_text.acceptableInput){
                value_warning.color = "#000000"
            } else {
                value_warning.color = "#ff0000"
            }
        }
    }


    //Button to override an out of bounds warning
    Button {
        id: override_button
        x: 350
        y: 115
        width: 110
        height: 20
        visible: true
        text: qsTr("Override warning")
        onClicked: {
            Sensor_Motor_Trim.value = value_text.text*1
            Sensor_Motor_Trim.index = component_list.currentIndex
            Sensor_Motor_Trim.press = 1
            component_list.model.get(component_list.currentIndex).normal = value_text.text*1
        }
    }

    //Text box for value
    TextField {
        id: value_text
        x: 207
        y: 161
        width: 70
        height: 20
        text: qsTr("0")
        font.pixelSize: 12
        validator: DoubleValidator {bottom: component_list.model.get(component_list.currentIndex).minimum;
                                    top: component_list.model.get(component_list.currentIndex).maximum;}
        onTextChanged: {
            if (value_warning != null) {
                if (this.acceptableInput){
                    value_warning.color = "#000000"
                } else {
                    value_warning.color = "#ff0000"
                }

                //value_warning.visible = !this.acceptableInput
            }
            if (override_button != null){
                override_button.visible = !this.acceptableInput
            }
            if (submit_button != null) {
                submit_button.enabled = this.acceptableInput
            }
        }

        onAccepted: {
            Sensor_Motor_Trim.value = this.text*1
            Sensor_Motor_Trim.index = component_list.currentIndex
            Sensor_Motor_Trim.press = 1
            component_list.model.get(component_list.currentIndex).normal = this.text*1
        }
    }

    Button {
        id: button_down10
        x: 101
        y: 161
        width: 30
        height: 20
        text: qsTr("-10")
        onClicked: {
            value_text.text = (value_text.text - 10).toFixed(1)
        }
    }

    Button {
        id: button_down1
        x: 135
        y: 161
        width: 30
        height: 20
        text: qsTr("-1")
        onClicked: {
            value_text.text = (value_text.text - 1).toFixed(1)
        }
    }

    Button {
        id: button_downTenth
        x: 169
        y: 161
        width: 30
        height: 20
        text: qsTr("-0.1")
        onClicked: {
            value_text.text = (value_text.text - 0.1).toFixed(1)
        }
    }

    Button {
        id: button_upTenth
        x: 285
        y: 161
        width: 30
        height: 20
        text: qsTr("+0.1")
        onClicked: {
            value_text.text = (value_text.text*1 + 0.1).toFixed(1)
        }
    }

    Button {
        id: button_up1
        x: 319
        y: 161
        width: 30
        height: 20
        text: qsTr("+1")
        onClicked: {
            value_text.text = (value_text.text*1 + 1).toFixed(1)
        }
    }

    Button {
        id: button_up10
        x: 353
        y: 161
        width: 30
        height: 20
        text: qsTr("+10")
        onClicked: {
            value_text.text = (value_text.text*1 + 10).toFixed(1)
        }
    }

    Text {
        id: current_value_text
        x: 101
        y: 141
        text: qsTr("Current Value: %1").arg(component_list.model.get(component_list.currentIndex).normal)
        font.pixelSize: 12
    }

}
