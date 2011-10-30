import QtQuick 1.0
import "../Ships"

Rectangle {
    id: panel
    anchors {
        right: parent.right
        left: parent.left
        rightMargin: -20
    }

    radius: 10

    height: mainWindow.height
    color: "steelblue"

    states: [
        State {
            name: "hidden"
            when: !parent.shown
            AnchorChanges { target: panel; anchors.left: parent.right}
        }
    ]

    ListView {
        spacing: 30
        interactive: false
        anchors.centerIn: parent
        width: parent.width - 20
        height: childrenRect.height
        model: ShipsModel {id: shipsModel}
        delegate: Ship { id: ship }
    }
}
