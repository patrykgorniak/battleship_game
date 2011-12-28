import QtQuick 1.1

ListModel {
    id: shipsModel

    ListElement { name: "Patrol boat"; boatSize: 1; quantity: 4; max: 4 }
    ListElement { name: "Submarine"; boatSize: 2; quantity: 3; max: 3 }
    ListElement { name: "Destroyer"; boatSize: 3; quantity: 2; max: 2 }
    ListElement { name: "Battleship"; boatSize: 4; quantity: 1; max: 1 }

    function reset() {
        for(var i=0;i<shipsModel.count;i++)
            shipsModel.get(i).quantity = shipsModel.get(i).max
    }
}
