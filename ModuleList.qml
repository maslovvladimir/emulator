import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Frame{
    property int deviceIndex: 0
    implicitWidth: 200
    implicitHeight: 150
    Text {
        id: moduleListCaption
        text: "Modules"
    }
    ListView {
        anchors.top: moduleListCaption.bottom
        anchors.topMargin: 3
        anchors.left:parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        orientation: Qt.Horizontal
        spacing: 10
        clip: true

        model: ListModel{
            ListElement{
                moduleName: "Main"
                moduleCode: 0
            }
            ListElement{
                moduleName: "Signal"
                moduleCode: 1
            }
        }

        delegate: Button{
            highlighted: true
            text: moduleName
            width: 80
            onClicked:deviceList.selectItem(deviceIndex, moduleCode)
        }
    }
}
