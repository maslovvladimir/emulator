import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import PropertyPage 1.0

Frame {
    anchors.fill: parent
    implicitHeight: 200
    implicitWidth: 300

    TextField{
        id: addressText
        anchors.left: parent.left
        anchors.leftMargin: 120
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        text: callibriCommon.address
        onEditingFinished: callibriCommon.address = text
    }
    TextField{
        id: firmwareText
        anchors.left: addressText.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: addressText.bottom
        anchors.topMargin: 10
        text: callibriCommon.firmware
        onEditingFinished: callibriCommon.firmware = text
    }
    TextField{
        id: buildText
        anchors.left: addressText.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: firmwareText.bottom
        anchors.topMargin: 10
        text: callibriCommon.build
        onEditingFinished: callibriCommon.build = text
    }
    TextField{
        id: radioFreqText
        anchors.left: addressText.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: buildText.bottom
        anchors.topMargin: 10
        text: callibriCommon.radioFreq
        onEditingFinished: callibriCommon.radioFreq = text
        enabled: false
    }
    ComboBox{
        id: extSwitchCombo
        anchors.left: addressText.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: radioFreqText.bottom
        anchors.topMargin: 10
        model: ListModel{
            ListElement{text: "Mio-Electrodes, Resp-USB"}
            ListElement{text: "Mio-Electrodes"}
            ListElement{text: "Mio-USB"}
            ListElement{text: "Resp-USB"}
        }
        currentIndex:  callibriCommon.extSwitchIndex
        onActivated:  callibriCommon.extSwitchIndex = currentIndex
    }
    TextField{
        id: batteryText
        anchors.left: addressText.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: extSwitchCombo.bottom
        anchors.topMargin: 10
        text: callibriCommon.batteryVoltage
        onEditingFinished: callibriCommon.batteryVoltage = text
    }
    Label{
        id: addressLabel
        text: "Address:"
        anchors.left: parent.left
        anchors.verticalCenter: addressText.verticalCenter
    }
    Label{
        id: firmwareLabel
        text: "Firmware version:"
        anchors.left: parent.left
        anchors.verticalCenter: firmwareText.verticalCenter
    }
    Label{
        id: buildLabel
        text: "Build version:"
        anchors.left: parent.left
        anchors.verticalCenter: buildText.verticalCenter
    }
    Label{
        id: radioFreqLabel
        text: "Radio frequency:"
        anchors.left: parent.left
        anchors.verticalCenter: radioFreqText.verticalCenter
    }
    Label{
        id: extSwitchLabel
        text: "External switch:"
        anchors.left: parent.left
        anchors.verticalCenter: extSwitchCombo.verticalCenter
    }
    Label{
        id: batteryLabel
        text: "Battery voltage, mV:"
        anchors.left: parent.left
        anchors.verticalCenter: batteryText.verticalCenter
    }

}
