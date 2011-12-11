import QtQuick 1.1
import GameManager 1.0
import "GameBoard"
import "Utils"

Item {
    id: root
    anchors.fill: parent
    property int _gameBoardLevel
    property GameManager m_manager: null
    property bool active: true
    signal restart

    GameBoard {
        width: _gameBoardLevel
        anchors.left:  parent.left
        anchors.verticalCenter: parent.verticalCenter
        model: m_manager.board
        interactionEnabled: false
        enabled: root.active
    }
    GameBoard {
        width: _gameBoardLevel
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        model: m_manager.boardEnemy
        enabled: root.active
    }

    Warning {
        id: warning
        text: "Gra zakończona!"
        btnText: "Zamknij"
        onClicked: root.restart();
    }


    Component.onCompleted: manager.gameFinished.connect(root.gameFinished)


    //Functions
    function gameFinished() {
        warning.visible = true
        root.active = false
    }
}
