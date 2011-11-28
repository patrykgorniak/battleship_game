import QtQuick 1.1
import GameManager 1.0
import "../GameBoard"
import "../Utils"

Item {
    id: configurator
    anchors.fill: parent
    property GameManager __manager

    signal closeAndStartGame();

    ShipsPanel {
        id: shipsPanel
        anchors.right: parent.right
        smooth: true
        z:1
        onShow: {
            if(!showed){
                if(configurator.checkIfAllShipsAdded())
                    configurator.closeAndStartGame()
                else
                {
                    warning.visible = true
                    shipsPanel.shown = true
                }

            }
        }
    }

    GameBoard {
        id: board
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        model: __manager.board
        z:0
        interactionEnabled: false
    }


    Warning {
        id: warning
        text: "Nie wybrano wszystkich statków."
        visible: false
    }

    function checkIfAllShipsAdded()
    {
        for (var i=0;i<4;i++)
            if(shipsPanel.__listView.model.get(i).quantity > 0)
                return false;
        return true;
    }
}
