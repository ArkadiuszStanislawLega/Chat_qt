import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Page {
    id: root
    padding: 20

    ColumnLayout{
        id: cl_content
        width: parent.width
        anchors.centerIn: parent
        spacing: 10

        GridLayout{
            columns: 2
            rows: 5
            width: parent.width-(2*parent.magins)

            Label{
                id: l_id
                font.pixelSize: 20
                text: qsTr("Id:")
            }

            TextField{
                id: tf_id
                height: 30
                Layout.fillWidth: true
                validator: IntValidator{
                    bottom: 1
                    top: 2000000
                }
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
                width: 300
                echoMode: TextInput.Password
            }
        }

        Row{
            id: buttons_row
            Layout.alignment: Qt.AlignHCenter | Qt.AlignHCenter
            spacing: 6

            RoundButton{
                id: register_button
                text: qsTr("Register")
                enabled: tf_password.length > 0 && tf_password.text === tf_repassword.text
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
