import QtQuick 2.0
import QtQuick.Window 2.2
import bluesat.owr 1.0



Window {
    id: main_window
    width: 800
    height: 800
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
        anchors.horizontalCenterOffset: 1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: logo.bottom
        anchors.topMargin: 75
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
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
        id: signal_strength_container
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 85
        anchors.left: logo.right
        anchors.leftMargin: 103
        anchors.bottom: video_pane.top
        anchors.bottomMargin: 16
        ROSSignalStrength {
            // @disable-check M16
            objectName: "signal_strength"
            id: signal_strength
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
            topic: qsTr("/rover/signal")
        }

    }



//===================================================================================


    //below is the task for SV-13



    Item {
        id: signal_strength_container_1
        anchors.bottomMargin: -94
        anchors.leftMargin: -494
        anchors.topMargin: 164
        anchors.right: parent.right
        anchors.rightMargin: 538
        anchors.top: parent.top
        anchors.left: logo.right
        anchors.bottom: video_pane.top
        ROSDrivingModeSwitching {
            // @disable-check M16
            objectName: "driving_mode_switching"
            id: driving_mode_switching
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
            topic: qsTr("/rover/driving_mode_switching")


//=====================================================================================================


                 Rectangle{
                    x:80
                   y:100
                   width:360
                   height:20
                   focus: true;
                   Keys.enabled: true;
                   Keys.forwardTo: [box_front,box_crab,box_four];




                    //rectangle for front wheel steering
                    Rectangle{
                        x:200
                        y:180
                        width:120
                        height:20
                        id: box_front
                        border.color: "black"
                        //focus:true
                        //
                        //Keys.enabled: true;
                        color:"white"
                        Text {
                            text: "front"
                                anchors.horizontalCenter:parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                font.pointSize:12
                                font.bold:true
                         }


                    }


                    Rectangle{
                        x:320
                        y:180
                        width:120
                        height:20
                        id: box_crab
                        border.color:"black"
                        //focus:true
                       // Keys.enabled: true;
                       color:"white"
                        Text {

                                text: "crab"
                                anchors.centerIn: parent
                                font.pointSize:12
                                font.bold:true
                         }


                    }


                    Rectangle{
                        x:440
                        y:180
                        width:120
                        height:20
                        id: box_four
                        border.color: "black"
                        //focus:true
                        //Keys.enabled: true;
                        color:"white"
                        Text {

                            text: "four"
                            anchors.horizontalCenter:parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            font.pointSize:12
                            font.bold:true
                         }



                    }







                    Keys.onPressed: {


                                switch(event.key){
                                //if A is pressed
                                //change color to red

                                case Qt.Key_A:
                                    box_front.color = "red"
                                    box_crab.color = "white";
                                    box_four.color="white"
                                    driving_mode_switching.sendmessage();
                                    break;

                                //if r is pressed
                                //change color to red
                                case Qt.Key_S:
                                    box_front.color = "white"
                                    box_crab.color = "red";
                                    box_four.color="white"
                                    driving_mode_switching.sendmessage();
                                    break;

                                case Qt.Key_D:
                                    box_front.color="white"
                                    box_crab.color = "white"
                                    box_four.color = "red"
                                    driving_mode_switching.sendmessage();
                                    break;
                                default:
                                    return;
                                }
                                event.accepted = true;

                  }












                }















//========================================================================================================

        }

    }








    /*
         Rectangle{
            x:80
           y:100
           width:360
           height:20
           focus: true;
           Keys.enabled: true;
           Keys.forwardTo: [box_front,box_crab,box_four];




            //rectangle for front wheel steering
            Rectangle{
                x:200
                y:180
                width:120
                height:20
                id: box_front
                border.color: "black"
                //focus:true
                //
                //Keys.enabled: true;
                color:"white"
                Text {
                    text: "front"
                        anchors.horizontalCenter:parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.pointSize:12
                        font.bold:true
                 }


            }


            Rectangle{
                x:320
                y:180
                width:120
                height:20
                id: box_crab
                border.color:"black"
                //focus:true
               // Keys.enabled: true;
               color:"white"
                Text {

                        text: "crab"
                        anchors.centerIn: parent
                        font.pointSize:12
                        font.bold:true
                 }


            }


            Rectangle{
                x:440
                y:180
                width:120
                height:20
                id: box_four
                border.color: "black"
                //focus:true
                //Keys.enabled: true;
                color:"white"
                Text {

                    text: "four"
                    anchors.horizontalCenter:parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize:12
                    font.bold:true
                 }



            }







            Keys.onPressed: {


                        switch(event.key){
                        //if A is pressed
                        //change color to red

                        case Qt.Key_A:
                            box_front.color = "red"
                            box_crab.color = "white";
                            box_four.color="white"

                            break;

                        //if r is pressed
                        //change color to red
                        case Qt.Key_S:
                            box_front.color = "white"
                            box_crab.color = "red";
                            box_four.color="white"
                            break;

                        case Qt.Key_D:
                            box_front.color="white"
                            box_crab.color = "white"
                            box_four.color = "red"
                            break;
                        default:
                            return;
                        }
                        event.accepted = true;

          }







        //}





        }



    */









//===================================================================================
}








