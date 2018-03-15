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
        text: "Cardiac"
        anchors.margins: 5
        anchors.left:parent.left
        anchors.top:parent.top
    }

}
