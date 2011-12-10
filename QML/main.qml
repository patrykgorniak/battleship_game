import QtQuick 1.1
import GameManager 1.0
import QtDesktop 0.1
import "content"
import "content/Utils"

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
        _manager: manager

        onCloseAndStartGame: {
            configurator.visible = false;
            game.visible = true
        }
    }

    DemoScreen {
        id: demo
        _game: game
        _bConfigurator: configurator
    }

    BusyIndicator {
        id: indicator
        on: false
    }

    function shipDestroyed() {
        console.log("destroyed")
    }
    function gameFinished() {
        console.log("gameFinished")
    }

    Component.onCompleted: {
        manager.shipDestroyed.connect(mainWindow.shipDestroyed)
        manager.gameFinished.connect(mainWindow.gameFinished)

        var now = new Date();
        var seed = now.getMilliseconds
        var num = Math.random(seed)

        console.log("NUMMMM" + num);
    }
}
