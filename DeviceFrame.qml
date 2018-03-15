import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import DeviceList 1.0

ItemDelegate {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 20
    implicitHeight: hasModules ? 300 : 270
    implicitWidth: 250
    Frame{
        id: frame
        anchors.fill: parent
        background: Rectangle{
            color: model.color
        }
        Button{
            id: removeButton
            anchors.right: parent.right
            anchors.top: parent.top
            width: 20
            height: 20
            text: "X"
            hoverEnabled: true
            highlighted: true
            onClicked: deviceList.removeItem(index)
        }
        Label {
            id: typeLabel
            anchors.margins: 20
            text: "Type:"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenter: comboBox.verticalCenter
        }
        ComboBox {
            id: comboBox
            anchors.top: deviceEnabledSwitch.bottom
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 48
            antialiasing: false
            anchors.right: parent.right
            anchors.rightMargin: 10
            editable: false
            model: ListModel{
                ListElement{text: "Brainbit"}
                ListElement{text: "Callibri"}
            }
            currentIndex: selectedTypeIndex
            onActivated: selectedTypeIndex = currentIndex
            enabled: !deviceEnabled
        }
        SwitchDelegate {
            id: deviceEnabledSwitch
            text: deviceEnabled ? "Enabled" : "Disabled"
            hoverEnabled: false
            checkable: true
            highlighted: false
            checked: deviceEnabled
            onClicked: deviceEnabled = checked;
        }
        Label{
            id: nameLabel
            color: "#26282a"
            text: "Name:"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenter: nameInput.verticalCenter
        }
        TextField {
            id: nameInput
            color: "#26282a"
            text: deviceName
            anchors.top: comboBox.bottom
            anchors.topMargin: 6
            anchors.left: comboBox.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 10
            font.pixelSize: 12
            onEditingFinished: deviceName = text
            enabled: !deviceEnabled
        }
        TextField {
            id: addressInput
            text: deviceAddress
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: nameInput.left
            anchors.leftMargin: 0
            anchors.top: nameInput.bottom
            anchors.topMargin: 6
            placeholderText: "00:00:00:00:00:00"
            onEditingFinished: deviceAddress = text
            enabled: !deviceEnabled
        }
        Label {
            id: label
            text: qsTr("Address:")
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenter: addressInput.verticalCenter
        }
        ModuleList{
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: addressInput.bottom
            anchors.bottom: parent.bottom
            anchors.margins: 6
            enabled: !deviceEnabled
            visible: hasModules
            deviceIndex: index
        }
        Button{
            highlighted: true
            text: "Edit"
            width: 80
            visible: !hasModules
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: addressInput.bottom
            anchors.margins: 12
            onClicked: deviceList.selectItem(index)
        }
    }
}

