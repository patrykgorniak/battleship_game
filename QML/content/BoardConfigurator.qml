import QtQuick 1.1
import GameManager 1.0
import "BoardConfigurator"

Item {
    anchors.fill: parent
    property GameManager _manager

    Configurator {
        id: configurator
        __manager: _manager
    }
}
