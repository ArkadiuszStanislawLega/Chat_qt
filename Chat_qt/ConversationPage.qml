import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Page {
    id: root
    property string inConversationWith

    header: ToolBar{
        ToolButton{
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }
    }

    Label{
        id: page_title
        text: inConvesationWith
        font.pixelSize: 20
        anchors.centerIn: parent
    }

    ColumnLayout{
        anchors.fill: parent

        ListView{
            id: list_view
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListViewBottomToTop
            spacing: 12
            model: 10
            delegate: Row {
                readonly property bool sent_by_me: index % 2 == 0

                anchors.right: sent_by_me ? list_view.contentItem : undefined
                spacing: 6

                Rectangle {
                   id: avatar
                   width: height
                   height: parent.height
                   color: "grey"
                   visible: !sent_by_me
                }

                Rectangle{
                    width: 80
                    height: 40
                    color: sent_by_me ? "lightGrey" : "steelblue"

                    Label{
                        anchors.centerIn: parent
                        text: index
                        color: sent_by_me ? "black" : "white"
                    }
                }
            }
            ScrollBar.vertical: ScrollBar{}
        }

        Pane{
            id: pane
            layout.fillWidth: true
        }
    }

}
