import QtQuick 1.1

Rectangle {
    id:element
    property bool hit: false

    border.width: 1
    border.color: "black"
    height: grid.height/10
    width: height

    MouseArea {
        anchors.fill: parent
        id:mouseArea
        hoverEnabled: true
    }

    states: [
        State {
            name: "hovered"
            when: mouseArea.containsMouse && !hit
            PropertyChanges {target: element; z: 5}
            PropertyChanges {target: element; border.color: "red"}
            PropertyChanges {target: element; border.width: 2}
            PropertyChanges {target: element; color: "lightblue"}
        }
    ]
}
