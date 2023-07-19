import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    width: 540
    height: 960
    visible: true
    title: qsTr("Chat")

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: ContactPage{

        }
    }
}
