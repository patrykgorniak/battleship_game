import QtQuick 1.1

Item {
    id:board
    width: 600
    height: width

    GridView {
        id:grid
        anchors.centerIn: parent

        width: board.width - 10
        height: width
        interactive: false

        cellHeight: grid.height/10
        cellWidth: cellHeight

        model: 100
        delegate: RectangleUnit {}
    }

    // functions

    function addShip(ship) {

    }
}
