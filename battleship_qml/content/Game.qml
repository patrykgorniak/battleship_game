import QtQuick 1.1
import "GameBoard"

Item {
    anchors.fill: parent
    property int _gameBoardLevel

    GameBoard {
        width: _gameBoardLevel
        anchors.left:  parent.left
        anchors.verticalCenter: parent.verticalCenter
    }
    GameBoard {
        width: _gameBoardLevel
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }
}
