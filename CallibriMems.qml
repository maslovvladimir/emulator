import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import PropertyPage 1.0

Frame {
    anchors.fill: parent
    implicitHeight: 200
    implicitWidth: 300

    ComboBox{
        id: accelSensCombo
        anchors.left: parent.left
        anchors.leftMargin: 120
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        model: ListModel{
            ListElement{text: "2g"}
            ListElement{text: "4g"}
            ListElement{text: "8g"}
            ListElement{text: "16g"}
        }
        currentIndex:  callibriCommon.selectedAccSensIndex
        onActivated:  callibriCommon.selectedAccSencIndex = currentIndex
    }

    ComboBox{
        id: gyroSensCombo
        anchors.left: accelSensCombo.left
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: accelSensCombo.bottom
        anchors.topMargin: 10
        model: ListModel{
            ListElement{text: "250 grad/s"}
            ListElement{text: "500 grad/s"}
            ListElement{text: "1000 grad/s"}
            ListElement{text: "2000 grad/s"}
        }
        currentIndex:  callibriCommon.selectedGyroSensIndex
        onActivated:  callibriCommon.selectedGyroSensIndex = currentIndex
    }

    Label{
        id: accelSensLabel
        text: "Accelerometer sens.:"
        anchors.left: parent.left
        anchors.verticalCenter: accelSensCombo.verticalCenter
    }

    Label{
        id: gyroSensLabel
        text: "Gyroscope sens.:"
        anchors.left: accelSensLabel.left
        anchors.verticalCenter: gyroSensCombo.verticalCenter
    }

}
