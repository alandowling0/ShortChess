import QtQuick 2.0

Item {
    id: root

    property int size: 8
    property bool rotateBoard: false

    signal pieceClicked(int x, int y)


    Repeater {
        id: piecesRepeater

        model: chessModel.piecesModel

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

            property real modelX: model.x
            property real modelY: model.y
            property bool selected: (model.x === chessModel.selected.x) && (model.y === chessModel.selected.y)

            opacity: selected ? 0.5 : 1.0

            Behavior on modelX {
                NumberAnimation {
                    easing.type: Easing.InOutQuad
                }
            }

            Behavior on modelY {
                NumberAnimation {
                    easing.type: Easing.InOutQuad
                }
            }

            x: modelX * width
            y: modelY * height
            height: root.height / root.size
            width: root.width / root.size

            Image {
                anchors.fill: parent
                source: piecesRepeater.pieceImagePath(model.type, model.color)
                rotation: root.rotateBoard ? 180 : 0
            }
        }
    }
}
