import QtQuick 1.1

Item {
    id:board
    width: 600
    height: width

    property alias model: grid.model
    property bool interactionEnabled: true

    GridView {
        id:grid
        anchors.centerIn: parent

        width: board.width - 10
        height: width
        interactive: false

        cellHeight: grid.height/10
        cellWidth: cellHeight

        delegate: RectangleUnit { interactionEnabled: board.interactionEnabled }
    }
}
