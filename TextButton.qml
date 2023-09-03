import QtQuick
import QtQuick.Controls

Component{
    id: textButton
    Item {
        Label {
            id: l_text
            text: dataModel.user.username
            font {
                pixelSize: 30
                bold: true
            }
        }
    }
}
