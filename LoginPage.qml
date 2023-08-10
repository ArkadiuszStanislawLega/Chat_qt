import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Page {
    id: root
    padding: 20

    ColumnLayout{
        width: parent.width
        anchors.centerIn: parent
        spacing: 10

        GridLayout{
            columns: 2
            rows: 3

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
        }

        Row{
            id: r_buttons
            spacing: 10
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            RoundButton{
                id: b_login
                text: qsTr("Login")
                enabled: tf_id.length > 0 && tf_password.length > 0
                onClicked:{
                    root.StackView.view.push("ContactPage.qml", {username: tf_id.text})
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
