import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    id: root

    property bool portrait: height >= width

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
        width: root.portrait ? parent.width : 50
        height: root.portrait ? 50 : parent.height

        portrait: root.portrait
        onSettingsClicked: drawer.open()
    }

    Item {
        id: boardArea

        anchors.top: root.portrait ? topBar.bottom : parent.top
        anchors.bottom: root.portrait ? bottomBarArea.top : parent.bottom
        anchors.left: root.portrait ? parent.left : topBar.right
        anchors.right: root.portrait ? parent.right : bottomBarArea.left
        anchors.margins: 5

        rotation: rotateSwitch.checked ? 180 : 0

        Behavior on rotation {
            NumberAnimation{}
        }

        Board {
            anchors.centerIn: parent
            height: Math.min(parent.height, parent.width)
            width: height

            size: 8

            onSquareClicked: chessModel.clickSquare(x, y)

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

    BottomBar {
        id: bottomBarArea

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: root.portrait ? parent.width : 50
        height: root.portrait ? 50 : parent.height

        onNewGameClicked: newGameConfirmationDialog.open()
        onTakeBackMoveClicked: chessModel.takebackMove()
        onRedoMoveClicked: chessModel.replayMove()
    }

    Drawer {
        id: drawer

        width: 0.66 * parent.width
        height: parent.height

        Column {
            Switch {
                id: rotateSwitch

                text: qsTr("Rotate Board")

                onCheckedChanged: drawer.close()
            }
        }
    }

    Item {
        anchors.fill: parent
        visible: newGameConfirmationDialog.visible

        MouseArea {
            anchors.fill: parent
            onClicked: {}
        }

        Dialog {
            id: newGameConfirmationDialog

            title: qsTr("New Game")

            contentItem: Item {
                anchors.fill: parent

                Text {
                    anchors.centerIn: parent
                    width: parent.width * 0.95

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    wrapMode: Text.WordWrap
                    text: qsTr("Are you sure you want to start a new game?")
                }
            }

            standardButtons: Dialog.Yes | Dialog.No

            onAccepted: chessModel.newGame()

            anchors.centerIn: parent
            width: 300
        }
    }
}
