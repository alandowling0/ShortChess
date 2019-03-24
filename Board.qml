import QtQuick 2.0

Item {
    id: root

    property int size: 8

    Repeater {
        model: root.size * root.size

        delegate: Item {
            property int rowIndex:  Math.floor(index / root.size)
            property int columnIndex: (index % root.size)
            property bool lightSquare: columnIndex % 2 === rowIndex % 2

            x: columnIndex * width
            y: rowIndex * height
            height: root.height / root.size
            width: root.width / root.size

            Rectangle {
                anchors.fill: parent

                color: parent.lightSquare ? "lightblue" : "steelblue"
            }
        }
    }
}
