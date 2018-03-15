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
        text: model.noiseAmplitude
        implicitWidth: 150
        anchors.margins: 5
        anchors.left:parent.left
        anchors.top:amplitudeLabel.bottom
    }
}
