import QtQuick 1.1

Rectangle {
    id:element
    property bool interactionEnabled: false
    property int _index: index
    signal mark(int modelData)
    border.width: 1
    border.color: "black"
    height: grid.height/10
    width: height
    opacity: 0.8

    Image {
        id: icon
        source: "../../../images/cross.png"
        anchors.fill: parent
        visible: modelData === -2 || modelData === -3
    }


    MouseArea {
        anchors.fill: parent
        id:mouseArea
        hoverEnabled: interactionEnabled
        enabled: true //interactionEnabled
        onClicked: {
            if(interactionEnabled)
                manager.shot(_index)
            else
                element.mark(modelData);
        }
    }

    Text {
        anchors.centerIn: parent
        id: text
        text: modelData > 0  ? modelData : ""
        font.bold: true
        font.pixelSize: 14
        color: "white"
    }

    states: [
        State {
            name: "hovered"
            when: mouseArea.containsMouse && interactionEnabled
            PropertyChanges {target: element; z: 5}
            PropertyChanges {target: element; border.color: "red"}
            PropertyChanges {target: element; border.width: 2}
            PropertyChanges {target: element; color: "lightblue"}
        }
    ]

    function takeColor(value) {
        switch(value){
        case -3: return "red" //trafiony
        case -2: return "red" //trafiony
        case -1: return "yellow"; //pudlo
        case 0: return "white";
        case 1: return "#02ff04";
        case 2: return "orange";
        case 3: return "brown";
        case 4: return "lightblue";
        case 5: return "lightgreen";
        case 6: return "blue";
        case 7: return "darkgreen";
        case 8: return "purple";
        case 9: return "#03bb01";
        }
        return "transparent"
    }

    Component.onCompleted: element.color = takeColor(modelData)
}
