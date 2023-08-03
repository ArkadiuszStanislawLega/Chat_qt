import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import io.qt.chat

Page {
    id: root

    Rectangle{
        width: root.width-20
        height: 250
        color: "transparent"
        anchors{
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
        }
        ColumnLayout{
            spacing: 6
            width: parent.width-20
            height: parent.height-20
            Layout.alignment: parent.Center

            Label{
                font.pixelSize: 20
                text: qsTr("Login:")
            }

            TextField {
                id: login_field
                height: 20
                width: parent.width-20
                validator: IntValidator{
                    bottom: 1
                    top: 2000000
                }
            }

            Label{
                font.pixelSize: 20
                text: qsTr("Password:")
            }


            TextField{
                id: password_field
                height: 20
                width: parent.width-20
                echoMode: TextInput.Password
            }

            Row{
                id: buttons_row
                spacing: 6
                Layout.alignment: parent.Center

                RoundButton{
                    id: login_button
                    text: qsTr("Login")
                    enabled: login_field.length > 0 && password_field.length > 0
                    onClicked:{
                        root.StackView.view.push("ContactPage.qml", {username: login_field.text})
                    }
                }

                RoundButton{
                    id: register_button
                    text: qsTr("Register")
                    onClicked:{
                        root.StackView.view.push("RegisterPage.qml")
                    }
                }
            }
        }
    }
}
