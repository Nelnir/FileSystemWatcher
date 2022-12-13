import QtQuick
import FSW.Controller 1.0
Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("File System Watcher")
    color: "#D2D2D2"

    Controller {id: controller; }
}
