import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: root
    visible: false
    anchors.fill: parent
    property bool running: false

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
            running: root.running ; from: 0; to: 360; loops: Animation.Infinite; duration: 1500
        }
    }

    Label {
        text: "Proszę czekać ..."
        color: "white"
        anchors { top: spiner.bottom; topMargin: 15; horizontalCenter: spiner.horizontalCenter }
        font.pixelSize: 22
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {}
    }

    onRunningChanged: root.visible = root.running
}
