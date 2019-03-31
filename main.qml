import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Component.onCompleted: gameController.newGame()

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
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Board {
            anchors.centerIn: parent
            height: Math.min(parent.height, parent.width)
            width: height

            size: 8

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    pieces.selectedX = -1
                    pieces.selectedY = -1
                    gameController.clearDestinations();
                }
            }

            Pieces {
                id: pieces

                anchors.fill: parent

                size: parent.size

                onPieceClicked: {
                    selectedX = x
                    selectedY = y

                    gameController.showDestinations(x, y)
                }
            }

            Highlights {
                anchors.fill: parent

                size: parent.size

                onDestinationClicked: {
                    const fromX = pieces.selectedX
                    const fromY = pieces.selectedY

                    if(fromX >= 0 && fromY >= 0) {
                        gameController.doMove(fromX, fromY, x, y)

                        pieces.selectedX = -1
                        pieces.selectedY = -1
                    }

                    gameController.clearDestinations();
                }
            }
        }
    }

    Drawer {
        id: drawer

        width: 0.66 * parent.width
        height: parent.height

        Button {
            text: "New Game"
            onClicked: {
                gameController.newGame()

                drawer.close()
            }
        }
    }
}
