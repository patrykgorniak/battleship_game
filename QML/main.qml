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
    state: "Introduction"

    Image {
        id: img
        source: "../images/ocean.jpg"
        anchors.fill: parent
    }

    BusyIndicator {
        id: indicator
        running: false
    }

    GameManager {
        id: manager
    }

    Game {
        id: gameScr
        visible: false
        _gameBoardLevel: parent.gameBoardLevel
        _manager: manager

        onRestart: {
            manager.restartGame()
        }
    }

    BoardConfigurator {
        id: configuratorScr
        visible: false
        _manager: manager

        onCloseAndStartGame: {
            mainWindow.state="Game"
        }
    }

    DemoScreen {
        id: introductionScr
        _game: gameScr
        _bConfigurator: configuratorScr
    }



    states: [
        State {
            name: "Game"
            PropertyChanges { target: introductionScr; visible: false; }
            PropertyChanges { target: gameScr; visible: true; }
        },
        State {
            name: "Configuration"
            PropertyChanges { target: introductionScr; visible: false; }
            PropertyChanges { target: configuratorScr; visible: true; }
        },
        State {
            name: "Introduction"
            PropertyChanges { target: introductionScr; visible: true; }
            PropertyChanges { target: configuratorScr; visible: false; }
            PropertyChanges { target: gameScr; visible: false; }
        }
    ]


    function handleRestart() {
//        configurator.visible = false;
//        gameScr.visible = false
//        introductionScr.visible = true
        mainWindow.state="Introduction"
        gameScr.interactive = true
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
        manager.restart.connect(mainWindow.handleRestart)
    }
}
