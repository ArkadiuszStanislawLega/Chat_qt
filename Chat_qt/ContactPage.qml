import QtQuick
import QtQuick.Window
import QtQuick.Controls

import io.qt.chat

Page{
    header: ToolBar {
        Label{
            text: qsTr("Contacts")
            font.pixelSize: 20
            anchors.centerIn: parent
            padding: 10
        }
    }

    ListView{
        id: list_view
        anchors.fill: parent
        topMargin: 48
        leftMargin: 48
        bottomMargin: 48
        rightMargin: 48
        spacing: 20
        model: SqlContactModel {}
        delegate: ItemDelegate {
            text: mode.display
            width: list_view.width - list_view.leftMargin - list_view.rightMargin
            height: avatar.implicitHeight
            leftPadding: avatar.implicitWidth + 32
            onClicked: root.StackView.view.push("ConversationPage.qml", {inConversationWith: modelData})

            Image {
                id: avatar
                source: "images/" + modelData.replace(" ", "_") + ".png"
            }

        }
    }
}
