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

        Row {
            anchors.centerIn: parent
            height: parent.height
            spacing: 10

            Item {
                id: buttonsModel

                Item {
                    function onClicked(){console.log("new game"); root.newGameClicked()}
                    property string image: "newgame.svg"
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

            Repeater {
                model: buttonsModel.children

                delegate: Item {
                    height: parent.height
                    width: height

                    Image {
                        anchors.fill: parent

                        source: "images/" + modelData.image

                        sourceSize.width: 50
                        sourceSize.height: 50

                        MouseArea {
                            anchors.fill: parent

                            onClicked: modelData.onClicked()
                        }
                    }
                }
            }
        }
    }
}
