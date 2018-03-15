import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import PropertyPage 1.0

Frame {
    anchors.fill: parent
    implicitHeight: 200
    implicitWidth: 300
    ComboBox{
        id: fsamplingCombo
        anchors.left: parent.left
        anchors.leftMargin: 120
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        model: ListModel{
            ListElement{text: "125"}
            ListElement{text: "250"}
            ListElement{text: "500"}
            ListElement{text: "1000"}
            ListElement{text: "2000"}
            ListElement{text: "4000"}
            ListElement{text: "8000"}
        }
        currentIndex: callibriSignal.samplingFrequencyIndex
        onActivated: callibriSignal.samplingFrequencyIndex = currentIndex
    }

    ComboBox{
        id: gainCombo
        anchors.left: fsamplingCombo.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: fsamplingCombo.bottom
        anchors.topMargin: 10
        model: ListModel{
            ListElement{text: "1"}
            ListElement{text: "2"}
            ListElement{text: "3"}
            ListElement{text: "4"}
            ListElement{text: "6"}
            ListElement{text: "8"}
            ListElement{text: "12"}
        }
        currentIndex: callibriSignal.gainIndex
        onActivated:  callibriSignal.gainIndex = currentIndex
    }

    TextField{
        id: offsetText
        anchors.left: fsamplingCombo.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: gainCombo.bottom
        anchors.topMargin: 10
        text: callibriSignal.offsetText
    }
    ComboBox{
        id: adcInputCombo
        anchors.left: fsamplingCombo.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: offsetText.bottom
        anchors.topMargin: 10
        model: ListModel{
            ListElement{text: "Electrodes"}
            ListElement{text: "Short"}
            ListElement{text: "ADC test"}
            ListElement{text: "Resistance"}
        }
        currentIndex:  callibriSignal.adcInputIndex
        onActivated:  callibriSignal.adcInputIndex = currentIndex
    }
    CheckBox{
        id: hpfCheckBox
        text: "Highpass filter";
        anchors.left:parent.left
        anchors.leftMargin: 5
        anchors.top:adcInputCombo.bottom
        checked: callibriSignal.hpfEnabled
    }
    RadioButton{
        id: sineSignalRadio
        anchors.top:hpfCheckBox.bottom
        anchors.left: fsamplingCombo.left
        anchors.topMargin: 10
        text:"Sine"
        checked: callibriSignal.sineRadioChecked
    }
    RadioButton{
        id: cardiacSignalRadio
        anchors.top:hpfCheckBox.bottom
        anchors.left: sineSignalRadio.right
        anchors.leftMargin: 3
        anchors.topMargin: 10
        text:"Cardiac"
        checked: callibriSignal.sineRadioChecked
    }
    RadioButton{
        id: noiseSignalRadio
        anchors.top:hpfCheckBox.bottom
        anchors.left: cardiacSignalRadio.right
        anchors.leftMargin: 3
        anchors.topMargin: 10
        text:"Noise"
        checked: callibriSignal.sineRadioChecked
    }
    RadioButton{
        id: fileSignalRadio
        anchors.top:hpfCheckBox.bottom
        anchors.left: noiseSignalRadio.right
        anchors.leftMargin: 3
        anchors.topMargin: 10
        text:"File"
        checked: callibriSignal.sineRadioChecked
    }
    SineSignalControls{
        anchors.top: sineSignalRadio.bottom
        anchors.margins: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: sineSignalRadio.checked
        model: callibriSignal
    }
    CardiacSignalControls{
        anchors.top: sineSignalRadio.bottom
        anchors.margins: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: cardiacSignalRadio.checked
        model: callibriSignal
    }
    NoiseSignalControls{
        anchors.top: sineSignalRadio.bottom
        anchors.margins: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: noiseSignalRadio.checked
        model: callibriSignal
    }
    FileSignalControls{
        anchors.top: sineSignalRadio.bottom
        anchors.margins: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: fileSignalRadio.checked
        model: callibriSignal
    }

    Label{
        id: fsamplingLabel
        text: "Sampling frequency:"
        anchors.left: parent.left
        anchors.verticalCenter: fsamplingCombo.verticalCenter
    }

    Label{
        id: gainLabel
        text: "Gain:"
        anchors.left: fsamplingLabel.left
        anchors.verticalCenter: gainCombo.verticalCenter
    }

    Label{
        id: offsetLabel
        text: "Offset:"
        anchors.left: fsamplingLabel.left
        anchors.verticalCenter: offsetText.verticalCenter
    }
    Label{
        id: adcInputLabel
        text: "ADC input:"
        anchors.left: fsamplingLabel.left
        anchors.verticalCenter: adcInputCombo.verticalCenter
    }
    Label{
        id: signalSelectorLabel
        text: "Signal type:"
        anchors.left: fsamplingLabel.left
        anchors.verticalCenter: sineSignalRadio.verticalCenter
    }
}
