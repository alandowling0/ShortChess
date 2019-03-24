import QtQuick 2.0

Item {
    id: root

    property int size: 8

    ListModel {
        id: pieceModel

        ListElement {
            color: "white"
            type: "pawn"
            row:  2
            column: 0
        }
        ListElement {
            color: "white"
            type: "rook"
            row: 0
            column:  1
        }
        ListElement {
            color: "black"
            type: "pawn"
            row: 1
            column: 3
        }
    }

    Repeater {
        id: piecesRepeater

        model: pieceModel

        function pieceImagePath(type, color) {
            let path = "images/"

            if(color === "white") {
                path += "White"
            }
            else {
                path += "Black"
            }

            if(type === "pawn") {
                path += "Pawn"
            }
            else if(type === "knight") {
                path += "Knight"
            }
            else if(type === "bishop") {
                path += "Bishop"
            }
            else if(type === "rook") {
                path += "Rook"
            }
            else if(type === "queen") {
                path += "Queen"
            }
            else if(type === "king") {
                path += "King"
            }

            path += ".png"

            return path
        }

        delegate: Item {
            id: piece

            property bool isMoving: false

            Behavior on x {
                enabled: piece.isMoving

                NumberAnimation {}
            }

            Behavior on y {
                enabled: piece.isMoving

                NumberAnimation {}
            }

            x: model.column * width
            y: model.row * height
            height: root.height / root.size
            width: root.width / root.size

            Image {
                anchors.fill: parent
                source: piecesRepeater.pieceImagePath(model.type, model.color)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    piece.isMoving = true
                    model.column = Math.floor(Math.random() * root.size)
                    model.row = Math.floor(Math.random() * root.size)
                    piece.isMoving = false
                }
            }
        }
    }

}
