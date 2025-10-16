import QtQuick

Window {
    visible: true
    width: 640
    height: 480
    title: "QML Hello"
    
    Text {
        anchors.centerIn: parent
        text: "Hello from QML!"
        font.pixelSize: 32
    }
}
