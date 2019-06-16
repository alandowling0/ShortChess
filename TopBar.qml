import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: root

    property string title: "Title"

    signal settingsClicked()

    Item {
        id: settingsIconArea

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: height

        Image {
            anchors.fill: parent
            anchors.margins: 3

            sourceSize.height: height
            sourceSize.width: width

            source: "images/settings.svg"

            MouseArea {
                anchors.fill: parent

                onClicked: root.settingsClicked()
            }
        }
    }

    Text {
        anchors.centerIn: parent

        font.pointSize: 24

        text: root.title
    }
}
