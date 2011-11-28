import QtQuick 1.1
import QtDesktop 0.1
import "Utils"

Rectangle {
    id: root
    anchors.fill: parent
    color: "transparent"
    property Game _game
    property BoardConfigurator _bConfigurator

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.7
    }

    ButtonRow {
        spacing: 10
        anchors.centerIn: parent
        Button {
            text: "Losuj planszę."
            width: 130
            height: 50
            onClicked: {
                root.visible = false;
                manager.generateBoard();
                _game.visible = true
            }
        }

        Button {
            text: "Ułóż planszę."
            width: 130
            height: 50
            onClicked: {
                root.visible = false;
                _bConfigurator.visible = true;
            }
        }
    }
}
