import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Page {
    id: root

    ColumnLayout{
        spacing: 6
        width: 100
        height: 100
        Layout.alignment: Qt.AlignCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Label{
            text: qsTr("Login:")
        }

        TextField {
            id: login_field
            width: 98
            height: 20
        }

        Label{
            text: qsTr("Password:")
        }

        TextInput{
            id: password_filed
            width: 98
            height: 20
            echoMode: TextInput.Password
        }

        Row{
            id: buttons_row
            spacing: 6

            RoundButton{
                id: login_button
                text: qsTr("Login")
                enabled: login_field.length > 0 && password_filed.length > 0
                onClicked:{
                    root.StackView.view.push("ContactPage.qml", {username: login_field.text})
                }
            }

            RoundButton{
                id: register_button
                text: qsTr("Register")
                onClicked:{
                }
            }
        }
    }
}
