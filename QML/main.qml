import QtQuick 1.1
import GameManager 1.0
import "content"

Rectangle {
    id: mainWindow
    width: 900
    height: 800
    property int gameBoardLevel: width > height ? width/2 : height/2

    Image {
        id: img
        source: "../images/ocean.jpg"
        anchors.fill: parent
    }

    GameManager {
        id: manager
    }

    Game {
        id: game
        _gameBoardLevel: parent.gameBoardLevel
        m_manager: manager
        visible: false
    }

    BoardConfigurator {
        id: configurator
        visible: false
    }

    DemoScreen {
        id: demo
        _game: game
    }

    function shipDestroyed() {
        console.log("destroyed")
    }
    function gameFinished() {
        console.log("gameFinished")
    }

    Component.onCompleted: {
        //console.log(manager.board);
        //console.log(manager.boardEnemy);
        manager.shipDestroyed.connect(mainWindow.shipDestroyed)
        manager.gameFinished.connect(mainWindow.gameFinished)
    }
}
