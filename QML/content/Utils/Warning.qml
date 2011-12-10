import QtQuick 1.1
import QtDesktop 0.1

Rectangle {
    id: root
    anchors.fill: parent
    color: "transparent"
    property alias text: txt.text
    property alias btnText: close.text
    z: 100

    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
        opacity: 0.9
    }

    Text {
        id: txt
        color: "white"
        anchors.centerIn: parent
        font.pixelSize: 22
    }

    Button {
        id: close
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: txt.bottom
        anchors.topMargin: 10
        text: "Zamknij"

        onClicked: root.visible = false
    }
}
