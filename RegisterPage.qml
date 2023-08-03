import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import io.qt.chat

Page {
    id: root
        ColumnLayout{
            spacing:  6
            width: parent.width-20
            anchors{
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }

            Label{
                font.pixelSize: 20
                text: qsTr("Id:")
            }

            TextField{
                id: id_field
                height: 20
                width: 400
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
                width: 400
                echoMode: TextInput.Password
            }

            TextField{
                id: repassword_field
                height: 20
                width: parent.width-20
                echoMode: TextInput.Password
            }

            Row{
                id: buttons_row
                spacing: 6
                Layout.alignment: parent.Center

                RoundButton{
                    id: register_button
                    text: qsTr("Register")
                    enabled: password_field.length > 0 && password_field.text == repassword_field.text
                    onClicked: {

                    }
                }

                RoundButton{
                    id: cancel_button
                    text: qsTr("Cancel")
                    onClicked: {
                        root.StackView.view.pop()
                    }
                }
            }
    }
}
