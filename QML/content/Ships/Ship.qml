import QtQuick 1.1

Rectangle {
    id: ship
    color:"transparent"
    width: childrenRect.width
    height: childrenRect.height
    property ListView view

    signal pickedUp(int m_x,int m_y);


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: undefined //ship
        drag.maximumX: mainWindow.width
        drag.maximumY: mainWindow.height
        onPressed: {
            console.log("Ship pressed: x: " + mouseX + "y: " + mouseY)
            var obj = ship.view.mapFromItem(ship,mouseX,mouseY);
            pickedUp(obj.x,obj.y)
        }
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

