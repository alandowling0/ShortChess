import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: root

    property string title: "Title"
    property bool portrait: true

    signal settingsClicked()

    Item {
        id: settingsIconArea

        anchors.top: parent.top
        anchors.left: parent.left
        height: 50
        width: 50

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
        visible: root.portrait
        anchors.centerIn: parent

        font.pointSize: 22

        text: root.title
    }
}
