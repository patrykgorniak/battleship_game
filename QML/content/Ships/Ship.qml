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
        drag.target: undefined // ship
        drag.maximumX: mainWindow.width
        drag.maximumY: mainWindow.height
        onPressed: {
            console.log("Ship pressed: x: " + mouseX + "y: " + mouseY)
            var obj = ship.view.mapFromItem(ship,mouseX,mouseY);
            pickedUp(obj.x,obj.y)
        }
    }

    Row {
        id: row
        anchors.leftMargin: 5
        Repeater {
            model: boatSize
            delegate: Rectangle {
                width: 45; height: width
                color: "transparent"
                border.width: 1
            }
        }
    }
    Text {
        id: txt
        text: " x " + quantity
        anchors.left: row.right
        anchors.leftMargin: 10
        anchors.verticalCenter: row.verticalCenter
        font.pixelSize: 18
    }
}

