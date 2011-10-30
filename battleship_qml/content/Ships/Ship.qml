import QtQuick 1.1

Rectangle {
    id: ship
    color:"transparent"
    width: childrenRect.width
    height: childrenRect.height


    MouseArea {
        id: mouseArea
        anchors.fill: parent

        drag.target: ship
        drag.maximumX: mainWindow.width
        drag.maximumY: mainWindow.height

    }

    Row {
        Repeater {
            model: boatSize
            delegate: Rectangle {
                width: 45; height: width
                color: "transparent"
                border.width: 1
            }
        }
    }
}

