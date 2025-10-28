import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    visible: true
    width: 360
    height: 520
    title: "QML Counter"
    readonly property color buttonTextColor: "#111111"

    Column {
        anchors.centerIn: parent
        spacing: 18
        width: parent.width - 40

        Text {
            id: greetingLabel
            text: appState.greeting
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            wrapMode: Text.WordWrap
        }

        Text {
            id: counterLabel
            text: `Count: ${appState.counter}`
            font.pointSize: 36
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }

        Row {
            spacing: 12
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                text: "-1"
                palette.buttonText: root.buttonTextColor
                onClicked: appState.decrement()
            }

            Button {
                text: "Reset"
                palette.buttonText: root.buttonTextColor
                onClicked: appState.reset()
            }

            Button {
                text: "+1"
                palette.buttonText: root.buttonTextColor
                onClicked: appState.increment()
            }
        }

        Row {
            spacing: 12
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                text: appState.autoRunning ? "Stop Worker" : "Start Worker"
                palette.buttonText: root.buttonTextColor
                onClicked: {
                    if (appState.autoRunning) {
                        appState.stopAutoIncrement()
                    } else {
                        appState.startAutoIncrement()
                    }
                }
            }

            Button {
                text: "Single Step"
                palette.buttonText: root.buttonTextColor
                onClicked: appState.increment()
            }

            Button {
                text: "Quit"
                palette.buttonText: root.buttonTextColor
                onClicked: Qt.quit()
            }
        }

        Column {
            spacing: 6
            width: parent.width

            Text {
                text: appState.autoRunning ? "Worker running" : "Worker idle"
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }

            Text {
                text: `Interval: ${appState.interval} ms`
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }

            Slider {
                id: intervalSlider
                from: 50
                to: 2500
                stepSize: 50
                value: appState.interval
                width: parent.width

                onMoved: appState.setInterval(Math.round(value))
                onValueChanged: {
                    if (!pressed) {
                        appState.setInterval(Math.round(value))
                    }
                }
            }
        }
    }
}
