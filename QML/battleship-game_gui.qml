import QtQuick 1.1

import "content"



Rectangle {
    id: mainWindow
    width: 900
    height: 800
    property int gameBoardLevel: width > height ? width/2 : height/2
    color: "lightgray"

    Game {
        id: game
        _gameBoardLevel: parent.gameBoardLevel
        visible: false
    }

    BoardConfigurator {
        id: configurator
//        visible: false
    }
}
