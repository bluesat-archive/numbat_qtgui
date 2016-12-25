import QtQuick 2.0
import QtQuick.Window 2.2
import bluesat.owr 1.0

Window {
    id: window1
    visible: true

    Image {
        id: image1
        x: 198
        y: 0
        width: 245
        height: 100
        fillMode: Image.PreserveAspectFit
        source: "/images/bluesatLogo.png"
    }

    ROSVideoComponent {
       // @disable-check M16
       objectName: "videoStream"
       id: videoStream
       // @disable-check M16
       anchors.bottom: parent.bottom
       // @disable-check M16
       anchors.bottomMargin: 0
       // @disable-check M16
       anchors.top: image1.bottom
       // @disable-check M16
       anchors.topMargin: 0
       // @disable-check M16
       width: 320
       // @disable-check M16
       height: 240
    }
}
