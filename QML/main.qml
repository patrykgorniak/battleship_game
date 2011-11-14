import QtQuick 1.1
import GameManager 1.0
import "content"

Rectangle {
    id: mainWindow
    width: 900
    height: 800
    property int gameBoardLevel: width > height ? width/2 : height/2
    color: "lightgray"

    GameManager {
        id: manager
    }

    Game {
        id: game
        _gameBoardLevel: parent.gameBoardLevel
//        visible: false
    }

    BoardConfigurator {
        id: configurator
        visible: false
    }

    Component.onCompleted: console.log(manager.board);
}
