import QtQuick 1.1
import GameManager 1.0
import "BoardConfigurator"

Item {
    id: root
    anchors.fill: parent
    property GameManager _manager
    signal closeAndStartGame

    Configurator {
        id: configurator
        __manager: _manager
        onCloseAndStartGame: root.closeAndStartGame()
    }
}
