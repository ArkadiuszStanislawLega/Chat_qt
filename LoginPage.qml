import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Page {
    id: root

    Rectangle{
        id: rec
        width: parent.width-40
        height: 250
        anchors.centerIn: parent
        color:"transparent"

        ColumnLayout{
            spacing: 6
            anchors.fill: parent
            Layout.alignment: parent.Center

            Label{
                font{
                    pixelSize: 20
                    bold: true
                }
                text: qsTr("Id:")
            }

            TextField {
                id: login_field
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
                id: password_field
                Layout.fillWidth: true
                height: 20
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
