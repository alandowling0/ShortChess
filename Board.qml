import QtQuick 2.0

Item {
    id: root

    property int size: 8

    signal squareClicked(int x, int y)

    Grid {
        columns: root.size

        Repeater
        {
            model: root.size * root.size

            delegate: Item {
                property int rowIndex:  Math.floor(index / root.size)
                property int columnIndex: (index % root.size)
                property bool lightSquare: columnIndex % 2 === rowIndex % 2

                height: root.height / root.size
                width: root.width / root.size

                Rectangle {
                    anchors.fill: parent

                    color: parent.lightSquare ? "lightblue" : "steelblue"
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: root.squareClicked(columnIndex, rowIndex)
                }
            }
        }
    }
}
