import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import io.qt.chat.user

Page {
    id: root
    padding: 20
    Keys.onReturnPressed: if(b_login.enabled) b_login.activate()

    Rectangle{
        anchors.fill: parent
        color: "darkgrey"
        anchors.centerIn: parent
    }

    ColumnLayout{
        id: cl
        width: parent.width - 40
        height: 250
        anchors.centerIn: parent
        spacing: 20

        Rectangle{
            anchors.fill: cl
            color: "grey"
            opacity: 0.6
        }

        GridLayout{
            columns: 2
            rows: 3
            width: cl.width - 20
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
        }

        Row{
            id: r_buttons
            spacing: 10
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            RoundButton{
                id: b_login
                text: qsTr("Login")
                enabled: tf_id.length > 0 && tf_password.length > 0

                function activate(){
                    user.password = tf_password.text;
                    user.dbId = tf_id.text;
                    user.isUserLogin();
                }

                onClicked: b_login.activate()
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
    Rectangle{
        id: info_background
        anchors{
            bottom: parent.bottom
            bottomMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
        height: 20
        width: parent.width
        color: "red"
        opacity: 0

        Label{
            id: info
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        OpacityAnimator {
            id: show_info_animation
            running: false
            target: info_background
            from: 0
            to: 1
            duration: 1000
            onFinished: hide_info_animation.start()
        }

        OpacityAnimator {
            id: hide_info_animation
            running: false
            target: info_background
            from: 1
            to: 0
            duration: 5000
        }
    }
}
