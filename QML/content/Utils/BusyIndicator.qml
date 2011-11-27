import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: root
    anchors.fill: parent

    property bool on: true

    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
        opacity: 0.8
    }

    Image {
        id: spiner
        source: "../../../images/arrows.png"
        smooth: true
        anchors.centerIn: parent

        NumberAnimation on rotation {
            running: root.on ; from: 0; to: 360; loops: Animation.Infinite; duration: 1500
        }
    }

    Label {
        text: "Proszę czekać ..."
        anchors { top: spiner.bottom; topMargin: 15 }

        font.pixelSize: 22
        color: "white"
        anchors.horizontalCenter: spiner.horizontalCenter
    }

    onOnChanged: root.visible = root.on
}
