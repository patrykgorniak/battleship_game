import QtQuick 1.0

Rectangle {
    id: shipsPanel
    width: 250
    property alias __listView: panel._listView;

    property bool shown: true
    signal show(bool showed)

    Panel {
        id: panel
    }

    SwitchButton {
        id: switchButton
        shown: parent.shown
        anchors {
            verticalCenter: panel.verticalCenter
            right: panel.left
        }

        onShow: {
            shipsPanel.show(shown)
        }
    }
}
