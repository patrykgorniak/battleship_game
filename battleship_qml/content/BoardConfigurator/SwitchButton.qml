import QtQuick 1.1

Rectangle {
    width: 20
    height: 50
    color: "blue"
    property bool shown: true

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
