import QtQuick 1.1
import GameManager 1.0
import "GameBoard"

Item {
    anchors.fill: parent
    property int _gameBoardLevel
    property GameManager m_manager: null

    GameBoard {
        width: _gameBoardLevel
        anchors.left:  parent.left
        anchors.verticalCenter: parent.verticalCenter
        model: m_manager.board
        interactionEnabled: false
    }
    GameBoard {
        width: _gameBoardLevel
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        model: m_manager.boardEnemy
    }
}
