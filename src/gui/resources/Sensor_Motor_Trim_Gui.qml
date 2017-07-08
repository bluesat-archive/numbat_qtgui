import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
//import bluesat.owr 1.0
import bluesat.owr.singleton 1.0

Item {
    id: sensor_motor_trim
    visible:true
    width: 600
    height: 250

    Component.onCompleted: {
        console.log("It worked")
    }

    Canvas {
        id: canvas
        Button {
            id: value_button
            x: 345
            y: 148
            height: 24
            text: qsTr("Submit")
            onClicked: {
                if (value_text.acceptableInput) {
                    //console.log("Button has been pressed...")
                    Sensor_Motor_Trim.value = value_text.text*1
                    Sensor_Motor_Trim.index = comboBox.currentIndex
                    Sensor_Motor_Trim.press = 1
                    comboBox.model.get(comboBox.currentIndex).normal = value_text.text*1
                }
            }
        }
    }

    Slider {
        id: value_slider
        x: 50
        y: 149
        width: 200
        height: 22
        maximumValue: 1500
        minimumValue: 500
        value: 1000
        onValueChanged: {
            if (value_text != null && this.pressed) {
                value_text.text = qsTr("%1").arg(this.value)
            }
        }
    }

    TextField {
        id: value_text
        x: 265
        y: 150
        width: 70
        height: 20
        text: qsTr("1000")
        font.pixelSize: 12
        validator: DoubleValidator {bottom: value_slider.minimumValue; top: value_slider.maximumValue;}
        onTextChanged: {
            if (value_slider != null) {
                value_slider.value = this.text*1
            }
            if (value_warning != null) {
                value_warning.visible = !this.acceptableInput
                override_button.visible = !this.acceptableInput
                value_button.enabled = this.acceptableInput
            }
            //console.log(this.text);
        }

        onAccepted: {
            //console.log("Text Submitted value")
            Sensor_Motor_Trim.value = this.text*1
            Sensor_Motor_Trim.index = comboBox.currentIndex
            Sensor_Motor_Trim.press = 1
            comboBox.model.get(comboBox.currentIndex).normal = this.text*1
        }
    }

    Text {
        id: value_warning
        x: 260
        y: 115
        width: 270
        height: 20
        color: "#ff0000"
        text: qsTr("Please enter a value between %1 and %2").arg(value_slider.minimumValue).arg(value_slider.maximumValue)
        visible: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
    }

    ComboBox {
        id: comboBox
        x: 50
        y: 115
        width: 200
        height: 20
        editable: false
        model: ListModel {
            id: cbItems
            ListElement {
                minimum: 500
                normal: 1000
                maximum: 1500
                text: "Banana"
            }
            ListElement {
                minimum: 50
                normal: 100
                maximum: 150
                text: "Apple"
            }
            ListElement {
                minimum: 5
                normal: 10
                maximum: 15
                text: "Coconut"
            }
        }

        Component.onCompleted: {
            console.log("Starting up...")
            Sensor_Motor_Trim.index = 0
            Sensor_Motor_Trim.init = 1
            while (Sensor_Motor_Trim.index < this.model.count){
                //console.log("Assigning %1 to index %2".arg(Sensor_Motor_Trim.value).arg(Sensor_Motor_Trim.index))
                this.model.get(Sensor_Motor_Trim.index).normal = Sensor_Motor_Trim.value
                Sensor_Motor_Trim.index ++
                if (Sensor_Motor_Trim.index > this.model.count - 1){
                    Sensor_Motor_Trim.init = 0
                } else {
                    Sensor_Motor_Trim.init = 1
                }
            }

            value_slider.minimumValue = this.model.get(this.currentIndex).minimum
            value_slider.maximumValue = this.model.get(this.currentIndex).maximum
            value_slider.value = this.model.get(this.currentIndex).normal
            value_text.text = qsTr("%1").arg(this.model.get(this.currentIndex).normal)
            if (value_text.acceptableInput){
                value_warning.visible = false
            } else {
                value_warning.visible = true
            }
            console.log("Done")
        }

        onCurrentTextChanged: {

            //console.log("Thing changed")
            //console.log(this.model.get(this.currentIndex).minimum)
            value_slider.minimumValue = this.model.get(this.currentIndex).minimum
            value_slider.maximumValue = this.model.get(this.currentIndex).maximum
            value_slider.value = this.model.get(this.currentIndex).normal
            value_text.text = qsTr("%1").arg(this.model.get(this.currentIndex).normal)
            if (value_text.acceptableInput){
                value_warning.visible = false
            } else {
                value_warning.visible = true
            }
        }
    }

    Button {
        id: override_button
        x: 420
        y: 148
        width: 110
        visible: false
        text: qsTr("Override warning")
        onClicked: {
            //console.log("Submitted out of range")
            Sensor_Motor_Trim.value = value_text.text*1
            Sensor_Motor_Trim.index = comboBox.currentIndex
            Sensor_Motor_Trim.press = 1
            comboBox.model.get(comboBox.currentIndex).normal = value_text.text*1
        }
    }

    Text {
        id: title
        x: 146
        y: 38
        text: qsTr("Trim Sensors/Joints")
        font.pixelSize: 32
    }

}
