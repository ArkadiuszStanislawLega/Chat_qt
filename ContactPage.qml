import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import com.iam_code.chat.contact_model
import com.iam_code.chat.user
import com.iam_code.chat.contact

Page {
    id: root
    property User user


    header: ChatToolBar {

        Label {
            id: l_info
            text: user.username ? user.username : user.dbId
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }
    ColumnLayout{
        anchors.fill: parent


    RowLayout {
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter
        TextField {
            id: tf_contact_id
            Layout.fillWidth: true
            height: 20
            validator: IntValidator {
                bottom: 1
                top: 200000
            }
        }

        RoundButton {
            id: b_add_contact
            text: qsTr("Add")
            enabled: true
            onClicked: {
                user.createContact(tf_contact_id.text);
            }
        }
    }

        ListView {
            id: list_view
            Layout.fillHeight: true
            Layout.fillWidth: true
            topMargin: 48
            leftMargin: 48
            bottomMargin: 48
            rightMargin: 48
            spacing: 20
            model: user.contacts
            delegate: ItemDelegate {
                text: model.display
                width: list_view.width - list_view.leftMargin - list_view.rightMargin
                height: avatar.implicitHeight
                leftPadding: avatar.implicitWidth + 32
                onClicked: root.StackView.view.push("ConversationPage.qml", {
                                                        "inConversationWith": model.display
                                                    })

                Label{
                    text: model.username
                }

                Image {
                    id: avatar
                    source: model.display === "Me" ? "" : "images/" + model.display.replace(
                                                         " ", "_") + ".png"
                }
            }
        }
    }
}
