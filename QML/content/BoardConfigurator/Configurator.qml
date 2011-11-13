import QtQuick 1.1
import "../GameBoard"

Item {
    id: configurator
    anchors.fill: parent

    ShipsPanel {
        anchors.right: parent.right
        smooth: true
        z:1
    }

    GameBoard {
        z:0
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
    }
}
