import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import FSW.Controller 1.0
import FSW.EventModel 1.0
import QtQuick.Dialogs
import Qt.labs.qmlmodels

Window {
    id: window
    width: 680
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
            text: qsTr("Watched paths:")
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
        }
        ListView{
            id: listView
            anchors.top: watched.bottom
            implicitHeight: contentItem.height
            implicitWidth: contentItem.width
            model: controller.model
            delegate: RowLayout{
                Text { text: modelData }
                Button { text: "Remove"; onClicked: controller.remove_path(index)}
            }
        }

        Button{
            id: plus
            text: "Add"
            anchors.left: watched.right
            anchors.leftMargin: 5
            onClicked: dialog.open()
        }
        Text{
            id: event
            text: qsTr("Event:")
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: listView.bottom
            anchors.topMargin: 10
        }
        TableView{
            id: tableView
            width: parent.width
            height: parent.height
            pointerNavigationEnabled: false
            animate: false
            anchors.top: header.bottom
            columnWidthProvider: function(index){
                switch(index){
                case 0: return 60
                case 1: return 400
                case 2: return 60
                case 3: return 150
                }
            }

            model: EventModel {
                id: eventModel
                Component.onCompleted: controller.set_event_model(this)
            }

            delegate: Rectangle{
                color: "transparent"
                implicitHeight: 25
                Text{
                    text: display
                    anchors.centerIn: parent
                }
            }

            Button{
                id: clear
                text: "Clear"
                anchors.top: parent.bottom
                onClicked: eventModel.reset()
            }
            Button{
                id: start
                text: "Start watching"
                anchors.top: parent.bottom
                anchors.left: clear.right
                onClicked: controller.start_watching()
            }
            Button{
                text: "Stop watching"
                anchors.top: parent.bottom
                anchors.left: start.right
                onClicked: controller.stop_watching()
            }
        }
        HorizontalHeaderView{
            id: header
            syncView: tableView
            anchors.top: event.bottom
        }
    }


    FolderDialog{
        id: dialog
        onAccepted:{
            controller.add_folder(dialog.selectedFolder)
        }
    }
}
