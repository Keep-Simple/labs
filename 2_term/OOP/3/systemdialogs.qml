import QtQuick
import QtQuick.Controls
import Qt.labs.platform

ApplicationWindow {
    visible: true
    title: "System Dialogs Gallery"
    width: 580
    height: 480
    Rectangle {
    width: 580
    height: 480

    Menu {
        id: zoomMenu

        MenuItem {
            text: qsTr("Zoom In")
            shortcut: StandardKey.ZoomIn
            onTriggered: zoomIn()
        }

        MenuItem {
            text: qsTr("Zoom Out")
            shortcut: StandardKey.ZoomOut
            onTriggered: zoomOut()
        }
    MenuItem {
        text: "Open..."
        onTriggered: fileDialog.open()
    }
    }

    // FileDialog {
        // id: fileDialog
        // folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    // }

    }


}
