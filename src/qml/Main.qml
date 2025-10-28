import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    visible: true
    width: 360
    height: 520
    title: "QML Counter"

    Column {
        anchors.centerIn: parent
        spacing: 16

        Text {
            id: greetingLabel
            text: appState.greeting
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
            width: 280
            wrapMode: Text.WordWrap
        }

        Text {
            id: counterLabel
            text: `Count: ${appState.counter}`
            font.pointSize: 32
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }

        Row {
            spacing: 12
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                text: "-1"
                onClicked: appState.decrement()
            }

            Button {
                text: "Reset"
                onClicked: appState.reset()
            }

            Button {
                text: "+1"
                onClicked: appState.increment()
            }
        }
    }
}
