import QtQuick
import QtQuick.Controls
import FSW.Controller 1.0
import QtQuick.Dialogs

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("File System Watcher")
    color: "#D2D2D2"

    Controller {id: controller; }

    Rectangle{
        id: layout
        anchors.margins: 5
        anchors.fill: parent
        color: "transparent"
        Text{
            id: watched
            text: qsTr("Watched directories:")
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
        }
        ListView{
            anchors.top: watched.bottom
            width: 100
            height: parent.height
            model: controller.model
            delegate: Row{
                Text { text: modelData }
            }
        }

        Button{
            id: plus
            text: "+"
            anchors.left: watched.right
            onClicked: dialog.open()
        }
        Button{
            id: minus
            text: "-"
            anchors.left: plus.right
            onClicked: controller.remove_last_folder()
        }
        Text{
            id: event
            text: qsTr("Event:")
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.verticalCenter
        }
        ListView{
            anchors.top: event.bottom
            width: 100
            height: parent.height
            model: controller.event_model
            delegate: Row{
                Text { text: modelData }
            }
        }
    }

    FolderDialog{
        id: dialog
        onAccepted:{
            controller.add_folder(dialog.selectedFolder)
        }
    }
}
