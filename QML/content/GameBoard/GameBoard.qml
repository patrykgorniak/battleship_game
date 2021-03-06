import QtQuick 1.1

Item {
    id:board
    width: 600
    height: width
    signal mark(int modelData)

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
        model: 100

        delegate: RectangleUnit { interactionEnabled: board.interactionEnabled; onMark: board.mark(modelData) }
    }
}
