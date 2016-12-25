import QtQuick 2.0
import QtQuick.Window 2.2

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
}
