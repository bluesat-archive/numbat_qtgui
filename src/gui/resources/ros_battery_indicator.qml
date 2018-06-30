import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import bluesat.owr.singleton 1.0

Item {
    Rectangle {
            id: battery_indicator
            property var charge: 33
            height: 15
            width: charge
            color: if (rect.width <= 0) {"Red"} else {"white"}
            x : 20
            y : 20
            border.width: 1
            focus: true
            Keys.enabled: true
            Keys.forwardTo: [rect]
            Keys.onEscapePressed: {
                Qt.quit;
            }
            Rectangle {
                width: 1
                height: 15
                x : battery_indicator.charge/3
                color: "black"
                border.width: 0
                z: 1
            }
            Rectangle {
                width: 1
                height: 15
                x : (battery_indicator.charge/3)*2
                color: "black"
                border.width: 0
                z: 1
            }
            Rectangle {
                x: battery_indicator.charge
                y: 4
                height:7
                width: 3
                color: "black"
            }
            Rectangle {
                id : rect
                height: 15
                width: battery_indicator.charge
                color: if(width > battery_indicator.charge) {"Red"} else if (width > 22) {"Green"} else if (width > 11) {"Yellow"} else {"Red"}
                border.width: 1
                Keys.enabled: true
                Keys.onPressed: {
                    switch(event.key)
                    {
                    case Qt.Key_Left: //when left is pressed, battery indicator decreases by
                            width -= (battery_indicator.charge)/20
                            break;
                    case Qt.Key_Right: //when right is pressed, battery indicator increases by 5
                            width += (battery_indicator.charge)/20
                            break;
                    }
                }

                Text {
                    x: battery_indicator.charge + 15
                    text: "%d", Math.round((rect.width/battery_indicator.charge)*100)
                }
                Text {
                    x: battery_indicator.charge + 5
                    text: "%"
                }
            }
    }
}
