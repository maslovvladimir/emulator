import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import Views 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: qsTr("Neurotech Device Emulator")
    header: ToolBar{
        id: mainToolBar
        Layout.fillWidth: true
        RowLayout {
            width: parent.width
            Text {
                text: "Service:"
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                leftPadding: 6
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.fillHeight: true
                Layout.fillWidth: false
            }
            Label {
                id: serverStateLabel
                text: serverPresenter.stateText
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
            }
            ToolButton {
                id: startServerButton
                text: "Start"
                rightPadding: 18
                leftPadding: 18
                enabled: serverPresenter.startButtonEnabled
                highlighted: serverPresenter.startButtonEnabled
                onClicked: serverPresenter.onStartClicked()
            }
            ToolButton {
                id: stopServerButton
                text: "Stop"
                Layout.fillWidth: false
                rightPadding: 18
                leftPadding: 18
                enabled: serverPresenter.stopButtonEnabled
                highlighted: serverPresenter.stopButtonEnabled
                onClicked: serverPresenter.onStopClicked()
            }
            Label {
                text: "Clients:"
                wrapMode: Text.WordWrap
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: false
            }
            Label {
                id: clientCountLabel
                text: "0"
                wrapMode: Text.WordWrap
                rightPadding: 6
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.fillHeight: true
                Layout.fillWidth: false
            }
        }
    }

    ServerPresenter{
        id: serverPresenter
    }

    DeviceList{
        id: deviceListFrame
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 320
        background: Rectangle{
            color: "#cccccc"
        }
    }

    PropertiesFrame {
        anchors.left: deviceListFrame.right
        anchors.top: parent.top
        anchors.right :parent.right
        anchors.bottom: parent.bottom
    }
}
