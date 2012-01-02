import QtQuick 1.1
import GameManager 1.0
import "GameBoard"
import "Utils"

Item {
    id: root
    anchors.fill: parent
    property int _gameBoardLevel
    property GameManager _manager: null
    property bool interactive: true
    signal restart

    GameBoard {
        width: _gameBoardLevel
        anchors.left:  parent.left
        anchors.verticalCenter: parent.verticalCenter
        model: _manager.board
        interactionEnabled: false
        enabled: root.interactive
    }

    GameBoard {
        width: _gameBoardLevel
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        model: _manager.boardEnemy
        enabled: root.interactive
    }

    Warning {
        id: warning
        text: "Gra zakończona!"
        btnText: "Zamknij"
        onClicked: root.restart();
    }

    Item {
        id: notifyItem
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        width: childrenRect.width
        height: childrenRect.height
        opacity: 0


        Behavior on opacity {
            NumberAnimation { duration: 1000 }
        }

        Rectangle {
            id: background
            radius: 5
            color: "white"
            opacity: 0.5
            height: 50
            width: 200
        }

        Rectangle {
            id: notify
            radius: 5
            color: "transparent"
            anchors.centerIn: background
            Text {
                id: txt
                text: "Statek został zniszczony!"
                anchors.centerIn: parent
            }
        }
    }

    Timer {
        id: timer
        interval: 2000
        repeat: true
        running: false
        onTriggered: { running = false; notifyItem.opacity = 0; }
    }


    Component.onCompleted: {
        manager.gameFinished.connect(root.gameFinished)
        manager.shipDestroyed.connect(root.shipDestroyed)
    }


    //Functions
    function gameFinished() {
        warning.visible = true
        root.interactive = false
    }

    function shipDestroyed() {
        timer.running = true
        notifyItem.opacity = 1
    }
}
