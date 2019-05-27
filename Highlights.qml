import QtQuick 2.0

Item {
    id: root

    property int size: 8

    signal destinationClicked(int x, int y)
    signal selectedClicked

    Repeater {
        model: chessModel.highlightsModel.destinations

        delegate: Item {

            height: root.height / root.size
            width: root.width / root.size
            x: modelData.x * width
            y: modelData.y * height

            Rectangle {
                anchors.fill: parent
                color: "green"
                opacity: 0.5
            }
        }
    }
}
