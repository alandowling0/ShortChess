import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: root

    property string title: "Title"

    signal menuClicked()

    Image {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 5
        width: 50

        height: Math.min(parent.height - 5, 50)

        source: "images/menu.png"

        MouseArea {
            anchors.fill: parent

            onClicked: root.menuClicked()
        }
    }

    Text {
        anchors.centerIn: parent

        font.pointSize: 24

        text: root.title
    }
}
