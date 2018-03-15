import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0
import DeviceList 1.0

Frame{
    implicitWidth: 250
    implicitHeight: 250
    ListView {
        id: devListView
        anchors.fill: parent
        spacing: 20
        clip: true
        ScrollBar.vertical: ScrollBar{
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        model: DeviceListModel{
            list: deviceList
        }

        delegate: DeviceFrame{
        }
    }
    RoundButton {
        id: addButton
        width: 35
        height: 35
        text: qsTr("+")
        highlighted: true
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        font.pixelSize: 18
        onClicked: deviceList.appendItem()
    }
    DropShadow {
            anchors.fill: addButton
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#80000000"
            source: addButton
        }
}
