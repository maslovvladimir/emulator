import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import PropertyPage 1.0

Frame {
    implicitHeight: 200
    implicitWidth: 300
    background: Rectangle {
        color: "#dddddd"
    }

    BrainbitProperties{
        visible: propertyPageModel.brainbitVisible
    }

    CallibriCommon{
        visible: propertyPageModel.callibriCommonVisible
    }

    CallibriSignal{
        visible: propertyPageModel.callibriSignalVisible
    }
}
