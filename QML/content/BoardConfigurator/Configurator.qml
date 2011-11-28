import QtQuick 1.1
import GameManager 1.0
import "../GameBoard"

Item {
    id: configurator
    anchors.fill: parent
    property GameManager __manager

    ShipsPanel {
        anchors.right: parent.right
        smooth: true
        z:1
    }

    GameBoard {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        model: __manager.board
        z:0
        interactionEnabled: false
    }
}
