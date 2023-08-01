import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import io.qt.chat

Page {
    id: root
    property string inConversationWith

    header: ChatToolBar{
        ToolButton{
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }
        Label{
            id: page_title
            text: inConversationWith
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }


    ColumnLayout{
        anchors.fill: parent

        ListView{
            id: list_view
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + message_field.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 12
            model: SqlConversationModel{
                recipient: inConversationWith
            }
            delegate: Column {
                anchors.right: sent_by_me ? list_view.contentItem.right : undefined
                spacing: 6

                readonly property bool sent_by_me: model.recipient !== "Me"

                Row{
                    id:message_row
                    spacing: 6
                    anchors.right: sent_by_me ? parent.right : undefined

                    Image{
                        id: avatar
                        source: !sent_by_me ? "images/" + model.author.replace(" ", "_") + ".png": ""
                    }
                    Rectangle{
                        width: Math.min(message_text.implicitWidth + 24,
                                        list_view.width - (!sent_by_me ? avatar.width + message_row.spacing : 0))
                        height: message_text.implicitHeight + 24
                        color: sent_by_me ? "lightgrey" : "steelblue"

                        Label{
                            id: message_text
                            text: model.message
                            color: sent_by_me ? "black" : "white"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }

                Label {
                    id: timestamp_text
                    text: Qt.formatDateTime(model.timestamp, "d MMM hh:mm")
                    color: "lightgrey"
                    anchors.right: sent_by_me ? parent.right : undefined
                }
            }
            ScrollBar.vertical: ScrollBar{}
        }

        Pane{
            id: pane
            Layout.fillWidth: true

            RowLayout{
                width: parent.width

                TextArea{
                    id: message_field
                    Layout.fillWidth: true
                    placeholderText: qsTr("Compose message")
                    wrapMode: TextArea.Wrap
                }

                Button {
                    id: send_button
                    text: qsTr("Send")
                    enabled:  message_field.length > 0
                    onClicked: {
                        list_view.model.send_message(inConversationWith, message_field.text);
                        message_field.text = "";
                    }
                }
            }
        }
    }

}
