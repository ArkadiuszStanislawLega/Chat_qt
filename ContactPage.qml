import QtQuick
import QtQuick.Window
import QtQuick.Controls

import io.qt.chat.contact_model

Page {
    id: root
    property string username

    header: ChatToolBar {
        Label {
            text: username
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ListView {
        id: list_view
        anchors.fill: parent
        topMargin: 48
        leftMargin: 48
        bottomMargin: 48
        rightMargin: 48
        spacing: 20
        model: SqlContactModel {}
        delegate: ItemDelegate {
            text: model.display
            width: list_view.width - list_view.leftMargin - list_view.rightMargin
            height: avatar.implicitHeight
            leftPadding: avatar.implicitWidth + 32
            onClicked: root.StackView.view.push("ConversationPage.qml", { inConversationWith: model.display })

            Image {
                id: avatar
                source: model.display === "Me" ? "" : "images/" + model.display.replace(" ", "_") + ".png"
            }
        }
    }
}
