import QtQuick 2.0

Item {
    id: root

    property int size: 8

    ListModel {
        id: highlightsModel

        ListElement {
            row: 0
            column: 0
        }
        ListElement {
            row: 0
            column: 2
        }
        ListElement {
            row: 3
            column: 3
        }
    }

    Repeater {
        id: highlightsRepeater

        model: highlightsModel

        delegate: Item {
            x: model.column * width
            y: model.row * height
            height: root.height / root.size
            width: root.width / root.size

            Rectangle {
                anchors.fill: parent
                color: "green"
                opacity: 0.5
            }
        }
    }

}
