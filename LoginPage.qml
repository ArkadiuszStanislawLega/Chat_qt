import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Page {
    id: root

    ColumnLayout{
        spacing: 6
        width: parent.width
        height: 200
        anchors.centerIn: parent

        Label{
            font{
                pixelSize: 20
                bold: true
            }
            text: qsTr("Id:")
        }

        TextField {
            id: tf_id
            Layout.fillWidth: true
            height: 20
            validator: IntValidator{
                bottom: 1
                top: 2000000
            }
        }

        Label{
            font{
                pixelSize: 20
                bold: true
            }

            text: qsTr("Password:")
        }


        TextField{
            id: tf_password
            Layout.fillWidth: true
            height: 20
            echoMode: TextInput.Password
        }

        Row{
            id: r_buttons
            spacing: 6
            Layout.alignment: parent.Center

            RoundButton{
                id: b_login
                text: qsTr("Login")
                enabled: tf_id.length > 0 && tf_password.length > 0
                onClicked:{
                    root.StackView.view.push("ContactPage.qml", {username: tf_login.text})
                }
            }

            RoundButton{
                id: b_register
                text: qsTr("Register")
                onClicked:{
                    root.StackView.view.push("RegisterPage.qml")
                }
            }
        }
    }
}
