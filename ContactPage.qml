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

    Contact {
        id: createContact
        onSuccessfullyCreated: {
            l_info.text = qsTr("Succesfully added contact.")
            //TODO: Add refresh list.
        }

        onCreatingFail: {
            l_info.text = qsTr("Fail to add contact.")
        }
    }

    header: ChatToolBar {

        Label {
            id: l_info
            text: user.username ? user.username : user.dbId
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        RowLayout {
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
                onClicked: {
                    createContact.ownerId = user.dbId
                    createContact.create()
                }
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
            model: user.contacts
            delegate: ItemDelegate {
                text: model.display
                width: list_view.width - list_view.leftMargin - list_view.rightMargin
                height: avatar.implicitHeight
                leftPadding: avatar.implicitWidth + 32
                onClicked: root.StackView.view.push("ConversationPage.qml", {
                                                        "inConversationWith": model.display
                                                    })

                Image {
                    id: avatar
                    source: model.display === "Me" ? "" : "images/" + model.display.replace(
                                                         " ", "_") + ".png"
                }
            }
        }
    }
}
