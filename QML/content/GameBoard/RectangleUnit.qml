import QtQuick 1.1

Rectangle {
    id:element
    property bool hit: false

    border.width: 1
    border.color: "black"
    height: grid.height/10
    width: height
    color: takeColor(modelData)

    MouseArea {
        anchors.fill: parent
        id:mouseArea
        hoverEnabled: true
    }

    Text {
        anchors.centerIn: parent
        id: text
        text: index
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

    function takeColor(value)
    {
        switch(value){
        case 0: return "white";
        case 1: return "#02ff04";
        case 2: return "orange";
        case 3: return "yellow";
        case 4: return "lightblue";
        case 5: return "lightgreen";
        case 6: return "blue";
        case 7: return "darkgreen";
        case 8: return "purple";
        }
    }
}
