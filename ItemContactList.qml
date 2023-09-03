import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Component {
    id: itemContactList
    Item {
        height: 40
        width: parent.width
        Button {
            id: button
            text: modelData.user.username
            anchors.fill: parent
            anchors.centerIn: parent
            onClicked: root.StackView.view.push("ConversationPage.qml", {
                                                    "contact": modelData,
                                                    "owner": user
                                                })

            background: Rectangle {
                anchors.fill: parent
                anchors.centerIn: parent
                color: "transparent"
                radius: 4
                RowLayout {
                    anchors.fill: parent
                    anchors.centerIn: parent
                    Label {
                        id: user_id
                        text: modelData.user.dbId
                        Layout.alignment: Qt.AlignRight
                        font {
                            pixelSize: 50
                            family: "TimesNewRoman"
                            italic: true
                        }
                        opacity: 0.5
                        color: "grey"
                    }
                }
            }
        }
    }
}
