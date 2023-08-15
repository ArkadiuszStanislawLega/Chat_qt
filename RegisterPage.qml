import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import com.iam_code.chat.user

Page {
    id: root
    padding: 20
    Keys.onReturnPressed: if(b_register.enabled) b_register.activate();
    Keys.onEscapePressed: root.StackView.view.pop();

    User{
        id: user
        onCreatedConfirmed: {
            info_background.visible = true
            info_background.color = "transparent";
            info.text = qsTr("Account created!");
            info.color = "white";

            l_id_from_db.text = user.dbId;
            tf_username.text = "";
            tf_password.text = "";
            tf_repassword.text = "";

            show_info_animation.start();
        }
        onCreatedError: {
            info_background.visible = true;
            info_background.color = "red";
            info.text = qsTr("Error");
            info.color = "white";

            show_info_animation.start();
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
                id: b_register
                text: qsTr("Register")
                enabled: tf_password.length > 0 && tf_password.text === tf_repassword.text

                function activate(){
                    user.username = tf_username.text;
                    user.password = tf_password.text;
                    user.registerUser();
                }

                onClicked: b_register.activate()
            }

            RoundButton{
                id: b_cancel
                text: qsTr("Back")

                function activate(){
                    root.StackView.view.pop();
                }

                onClicked: b_cancel.activate()
            }
        }
    }
    Rectangle{
        id: info_background
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        height: 20
        width: parent.width
        opacity: 0

        Label{
            id: info
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
