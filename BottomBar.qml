import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: root

    signal newGameClicked()
    signal takeBackMoveClicked()
    signal redoMoveClicked()
    signal moveNowClicked()

    Rectangle {
        anchors.fill: parent

        color: "transparent"

        Item {
            id: buttonsModel

            Item {
                function onClicked(){console.log("new game"); root.newGameClicked()}
                property string image: "newgame.svg"
                property bool enabled: chessModel.newGameAvailable
            }

            Item {
                function onClicked(){console.log("takebackmove"); root.takeBackMoveClicked()}
                property string image: "takebackmove.svg"
            }

            Item {
                function onClicked(){console.log("redomove"); root.redoMoveClicked()}
                property string image: "redomove.svg"
            }

            Item {
                function onClicked(){console.log("movenow"); root.moveNowClicked()}
                property string image: "movenow.svg"
            }
        }

        Component {
            id: button

            Item {
               height: 50
               width: 50

               opacity: modelData.enabled ? 1.0 : 0.5

               Image {
                   anchors.fill: parent

                   source: "images/" + modelData.image

                   sourceSize.width: 50
                   sourceSize.height: 50

                   MouseArea {
                       anchors.fill: parent

                       enabled: modelData.enabled
                       onClicked: modelData.onClicked()
                   }
               }
           }
        }

        Row {
            visible: root.height <= root.width
            anchors.centerIn: parent
            height: parent.height
            spacing: 10

            Repeater {
                model: buttonsModel.children

                delegate: button
            }
        }

        Column {
            visible: root.height > root.width
            anchors.centerIn: parent
            width: parent.width
            spacing: 10

            Repeater {
                model: buttonsModel.children

                delegate: button
            }
        }
    }
}
