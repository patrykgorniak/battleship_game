import QtQuick 1.1

Rectangle {
    width: 20
    height: 50
    color: "transparent"
    property bool shown: true

    Rectangle {
        id: background
        anchors.fill: parent
        color: "darkgreen"
        opacity: 0.6
    }

//signals
    signal show(bool shown)

// components

    Text {
        anchors.centerIn: parent
        text: shown ? ">>" : "<<"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: show(!shown)
    }
}
