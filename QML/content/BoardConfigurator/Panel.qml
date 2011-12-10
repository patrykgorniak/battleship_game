import QtQuick 1.0
import QtDesktop 0.1
import "../Ships"

Rectangle {
    id: panel
    height: mainWindow.height
    color: "transparent"
    radius: 10
    anchors { right: parent.right; left: parent.left; rightMargin: -20; }
    property alias _listView: listView

    states: [
        State {
            name: "hidden"
            when: !parent.shown
            AnchorChanges { target: panel; anchors.left: parent.right}
        }
    ]

    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
        opacity: 0.2
        radius: panel.radius
    }

    Text {
        id: txt
        anchors { top: parent.top; left: parent.left; right: parent.right; margins: 10}
        text: "Wybierz jeden ze statków,\nnastępnie kliknij dodaj aby dodać\nna planszę."
        font { pixelSize: 14; bold: true}
        color: "lightgray"
        font.family: "Helvetica"
        horizontalAlignment: Text.AlignHCenter
    }

    ListView {
        id: listView
        spacing: 30
        clip: true
        interactive: false
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 50
        height: childrenRect.height + 20
        model: ShipsModel { id: shipsModel }
        delegate: Ship {
            id: ship;
            view: listView;
            onPickedUp: {
                var index = listView.indexAt(m_x,m_y)
                listView.currentIndex = index
                //                shipsModel.move(index, listView.count-1, 1)
            }
        }

        highlight: Rectangle {
            color: "red"
            opacity: 0.3
            width: parent.width
            border.width: 1
        }
    }

    ButtonRow {
        id: buttons
        anchors.top: listView.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 5

        Button {
            id: add
            text: "Dodaj statek"
            width: panel.width / 2 - 25
            height: 50
            enabled: listView.model.get(listView.currentIndex).quantity > 0
            onClicked: {
                listView.model.get(listView.currentIndex).quantity -= 1
                manager.addShip(listView.model.get(listView.currentIndex).boatSize);
            }
        }
        Button {
            id: del
            text: "Usuń statek"
            width: panel.width / 2 - 25
            //            enabled: listView.model.get(listView.currentIndex).quantity < listView.model.get(listView.currentIndex).max
            height: 50
            onClicked: {
                var ship = manager.removeShip(shipNB.text)
                if(ship>0)
                    listView.model.get(ship-1).quantity += 1
                shipNB.text = "";
                //                if ( listView.model.get(listView.currentIndex).quantity < listView.model.get(listView.currentIndex).max)
                //                    listView.model.get(listView.currentIndex).quantity += 1
            }
        }
    }

    ButtonRow {
        id: editor
        spacing: 30
        anchors.top: buttons.bottom
        anchors.margins: 10
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            text: "Numer statku: "
            anchors.verticalCenter: shipNB.verticalCenter
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            id: shipNB
            width: 100
            text: ""
            validator: IntValidator { }

            onTextChanged: {
                panel.checkMove()
            }
        }
    }

    Item {
        id: control
        anchors.margins: 20
        anchors.top: editor.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: width

        Image {
            id:topIMG
            source: "../../../images/arrow.png"
            rotation: 90
            height: control.height / 5
            width: height
            anchors.top:  parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: topIMGMouse.containsMouse && enabled ? 1 : 0.5
            enabled: false

            MouseArea {
                id: topIMGMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    manager.moveShip(shipNB.text,-1,0);
                    panel.checkMove()
                    //                    topIMG.enabled = manager.validateShipPosition(shipNB.text,-1,0);
                }
            }
        }

        Image {
            id: rightIMG
            source: "../../../images/arrow.png"
            rotation: 180
            height: control.height / 5
            width: height
            anchors.left: topIMG.right
            anchors.top: topIMG.bottom
            opacity: rightIMGMouse.containsMouse && enabled ? 1 : 0.5
            enabled: false

            MouseArea {
                id: rightIMGMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    manager.moveShip(shipNB.text,0,1);
                    panel.checkMove()
                    //                    rightIMG.enabled = manager.validateShipPosition(shipNB.text,0,1);
                }
            }
        }

        Image {
            id: bottomIMG
            source: "../../../images/arrow.png"
            rotation: 270
            height: control.height / 5
            width: height
            anchors.top: rightIMG.bottom
            anchors.right: topIMG.right
            opacity: bottomIMGMouse.containsMouse && enabled ? 1 : 0.5
            enabled: false

            MouseArea {
                id: bottomIMGMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    manager.moveShip(shipNB.text,1,0);
                    panel.checkMove()
                    //                    bottomIMG.enabled = manager.validateShipPosition(shipNB.text,1,0);
                }
            }
        }

        Image {
            id: leftIMG
            source: "../../../images/arrow.png"
            rotation: 0
            height: control.height / 5
            width: height
            anchors.right: topIMG.left
            anchors.top: rightIMG.top
            opacity: leftIMGMouse.containsMouse && enabled ? 1 : 0.5
            enabled: false

            MouseArea {
                id: leftIMGMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    manager.moveShip(shipNB.text,0,-1);
                    panel.checkMove()
                    //                    leftIMG.enabled = manager.validateShipPosition(shipNB.text,0,-1)
                }
            }
        }

        Image {
            id: leftRotateIMG
            source: "../../../images/arrow.png"
            rotation: 0
            height: control.height / 5
            width: height
            anchors.right: bottomIMG.left
            anchors.top: bottomIMG.top
            anchors.topMargin: 10
            anchors.rightMargin: 10
            opacity: leftRotateIMGMouse.containsMouse && enabled ? 1 : 0.5

            MouseArea {
                id: leftRotateIMGMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {

                }
            }
        }

        Image {
            id: rightRotateIMG
            source: "../../../images/arrow.png"
            rotation: 180
            height: control.height / 5
            width: height
            anchors.left: bottomIMG.right
            anchors.top: bottomIMG.top
            anchors.topMargin: 10
            anchors.leftMargin: 10
            opacity: rightRotateIMGMouse.containsMouse && enabled ? 1 : 0.5

            MouseArea {
                id: rightRotateIMGMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {

                }
            }
        }
    }


    // TODO::PG:Add rotation logic
    function checkMove()
    {
        topIMG.enabled = manager.validateShipPosition(shipNB.text,-1,0)
        rightIMG.enabled = manager.validateShipPosition(shipNB.text,0,1)
        bottomIMG.enabled = manager.validateShipPosition(shipNB.text,1,0)
        leftIMG.enabled =  manager.validateShipPosition(shipNB.text,0,-1)
//        rightRotateIMG.enabled =
//        leftRotateIMG.enabled =
    }
}
