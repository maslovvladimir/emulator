import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import PropertyPage 1.0

Frame {
    implicitHeight: 200
    implicitWidth: 200
    property QtObject model: undefined

    Label{
        id:amplitudeLabel
        text: "Ampltude, uV"
        anchors.margins: 5
        anchors.left:parent.left
        anchors.top:parent.top
    }
    TextField{
        id: amplitudeText
        text: model.sineAmplitude
        implicitWidth: 150
        anchors.margins: 5
        anchors.left:parent.left
        anchors.top:amplitudeLabel.bottom
    }
    Label{
        id:frequencyLabel
        text: "Frequency, Hz"
        anchors.margins: 5
        anchors.left:parent.left
        anchors.top:amplitudeText.bottom
    }
    TextField{
        id:frequencyText
        text: model.sineFrequency
        implicitWidth: 150
        anchors.margins: 5
        anchors.left:parent.left
        anchors.top:frequencyLabel.bottom
    }

    Label{
        id:phaseLabel
        text: "Phase, grad"
        anchors.margins: 5
        anchors.left:parent.left
        anchors.top:frequencyText.bottom
    }
    TextField{
        text: model.sinePhase
        implicitWidth: 150
        anchors.margins: 5
        anchors.left:parent.left
        anchors.top:phaseLabel.bottom
    }
}
