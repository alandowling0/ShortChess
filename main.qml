import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent

        gradient: Gradient {
            GradientStop { position: 0.0; color: "brown" }
            GradientStop { position: 1.0; color: "darkred" }
        }
    }

    TopBar {
        id: topBar

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50

        onMenuClicked: drawer.open()
    }

    Item {
        id: boardArea

        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        rotation: rotateSwitch.checked ? 180 : 0

        Board {
            anchors.centerIn: parent
            height: Math.min(parent.height, parent.width)
            width: height

            size: 8

            onSquareClicked: {
                chessModel.selectSquare(x, y)
            }

            Pieces {
                id: pieces

                anchors.fill: parent

                size: parent.size

                rotateBoard: rotateSwitch.checked
            }

            Highlights {
                anchors.fill: parent

                size: parent.size
            }
        }
    }

    Drawer {
        id: drawer

        width: 0.66 * parent.width
        height: parent.height

        Column {
            Button {
                text: "New Game"
                onClicked: {
                    chessModel.newGame()

                    drawer.close()
                }
            }

            Switch {
                id: rotateSwitch

                text: "Rotate Board"
            }
        }
    }
}
