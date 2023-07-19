import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    width: 540
    height: 960
    visible: true
    title: qsTr("Chat")

    Page{
        anchors.fill: parent
        header: Label {
            padding: 10
            text: qsTr("Contacts")
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        ListView{
            id: list_view
            anchors.fill: parent
            topMargin: 48
            leftMargin: 48
            bottomMargin: 48
            rightMargin: 48
            spacing: 20
            model: ["Albert Einstein" , "Ernest Hemingway", "Hans Gude"]
            delegate: ItemDelegate {
                text: modelData
                width: list_view.width - list_view.leftMargin - list_view.rightMargin
                height: avatar.implicitHeight
                leftPadding: avatar.implicitWidth + 32


                Image {
                    id: avatar
                    source: "images/" + modelData.replace(" ", "_") + ".png"
                }

            }
        }
    }
}
