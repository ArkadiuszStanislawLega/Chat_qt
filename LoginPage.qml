import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Page {
    id: root
    anchors.horizontalCenter: parent.horizontalCenter
    ColumnLayout{
        anchors.fill: parent
        spacing: 2
        width: 200
        height: 200
        Layout.alignment: Qt.AlignCenter

        TextField {
            id: login_field
            width: 60
            height: 20
        }

        TextField{
            id: password_filed
            width: 60
            height: 20
        }


        RoundButton{
            id: login_button
            text: qsTr("Login")
            enabled: login_field.length > 0 && password_filed.length > 0
            onClicked:{
                root.StackView.view.push("ContactPage.qml", {username: login_field.text})
            }
        }
    }
}
