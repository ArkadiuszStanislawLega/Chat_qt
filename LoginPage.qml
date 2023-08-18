import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import com.iam_code.chat.user

Page {
    id: root
    Keys.onReturnPressed: if (b_login.enabled)
                              b_login.activate()

    User {
        id: user
        onLoginInFail: show_info_animation.start()
        onIsLoginIn: root.StackView.view.push("ContactPage.qml", {
                                                  "user": user
                                              })
    }

    Rectangle {
        anchors {
            fill: parent
            centerIn: parent
        }
        color: "darkgrey"
    }

    Rectangle {
        width: l_login.width + 20
        height: l_login.height + 20
        anchors.centerIn: l_login
        radius: 20
        color: "black"
        opacity: 0.4
    }

    ColumnLayout {
        id: l_login
        spacing: 10
        width: parent.width - 40
        height: 200
        anchors.centerIn: parent

        Label {
            text: "Login in"
            font {
                pixelSize: 40
                bold: true
                family: "TimesNewRoman"
            }
            color: "#70a1ee"
            Layout.alignment: Qt.AlignHCenter
        }

        GridLayout {
            columns: 2
            rows: 2
            Layout.alignment: Qt.AlignHCenter

            Label {
                font {
                    pixelSize: 20
                    bold: true
                }
                text: qsTr("Id:")
            }

            TextField {
                id: tf_id
                Layout.fillWidth: true
                height: 20
                validator: IntValidator {
                    bottom: 1
                    top: 2000000
                }
            }

            Label {
                font {
                    pixelSize: 20
                    bold: true
                }
                text: qsTr("Password:")
            }

            TextField {
                id: tf_password
                Layout.fillWidth: true
                height: 20
                echoMode: TextInput.Password
            }
        }

        Row {
            id: r_buttons
            spacing: 10
            Layout.alignment: Qt.AlignHCenter

            RoundButton {
                id: b_login
                text: qsTr("Login")
                enabled: tf_id.length > 0 && tf_password.length > 0

                function activate() {
                    user.dbId = tf_id.text
                    user.password = tf_password.text
                    user.isUserLogin()
                }

                onClicked: b_login.activate()
            }

            RoundButton {
                id: b_register
                text: qsTr("Register")
                onClicked: {
                    root.StackView.view.push("RegisterPage.qml")
                }
            }
        }
    }

    Rectangle {
        id: info_background
        anchors {
            bottom: parent.bottom
            bottomMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
        height: 20
        width: parent.width
        color: "red"
        opacity: 0

        Label {
            id: info
            text: "Wrong Id or password."
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
