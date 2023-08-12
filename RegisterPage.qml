import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import io.qt.chat.user

Page {
    id: root
    padding: 20

    User{
        id: user
        onCreatedConfirmed: {
            info_backgroud.visible = true
            info.text = qsTr("Created")
            info.color = "black"
            info_backgroud.color = "transparent"
        }
        onCreatedError: {
            info_backgroud.visible = true
            info.text = qsTr("Error");
            info.color = "white"
            info_backgroud.color = "red"
        }
    }

    ColumnLayout{
        id: cl_content
        width: parent.width
        anchors.centerIn: parent
        spacing: 10

        GridLayout{
            columns: 2
            rows: 4

            Label{
                id: l_id_info
                font.pixelSize: 20
                text: qsTr("Account id:")
            }

            Label{
                id: l_id_from_db
                font {
                    pixelSize: 20
                    italic: true
                }
                text: user.dbId
            }

            Label{
                id: l_username
                font.pixelSize: 20
                text: qsTr("Username (optional):")
            }

            TextField{
                id: tf_username
                height: 30
                Layout.fillWidth: true
            }

            Label{
                id: l_password
                font.pixelSize: 20
                text: qsTr("Password:")
            }

            TextField{
                id: tf_password
                height: 30
                Layout.fillWidth: true
                echoMode: TextInput.Password
            }

            Label{
                id: l_repassword
                font.pixelSize: 20
                text: qsTr("Retype password:")
            }

            TextField{
                id: tf_repassword
                Layout.fillWidth: true
                height: 30
                echoMode: TextInput.Password
            }

        }

        Row{
            id: buttons_row
            Layout.alignment: Qt.AlignHCenter | Qt.AlignHCenter
            spacing: 10

            RoundButton{
                id: register_button
                text: qsTr("Register")
                enabled: tf_password.length > 0 && tf_password.text === tf_repassword.text
                onClicked: {
                    user.username = tf_username.text;
                    user.password = tf_password.text;
                    user.registerUser();
                }
            }

            RoundButton{
                id: cancel_button
                text: qsTr("Back")
                onClicked: {
                    root.StackView.view.pop();
                }
            }
        }
    }
    Rectangle{
        id: info_backgroud
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        height: 20
        width: parent.width
        visible: false

        Label{
            id: info
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
