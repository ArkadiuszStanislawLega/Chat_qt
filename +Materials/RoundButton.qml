import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects

Button {
    id: control

    Material.theme: Material.Dark

    background: Rectangle {
        implicitWidth: 48
        implicitHeight: 48
        color: Material.accentColor
        radius: width / 2

        layer.enabled: control.enabled
        layer.effect: DropShadow {
            verticalOffset: 1
            color: Material.dropShadowColor
            samples: control.pressed ? 20 : 10
            spread: 0.5
        }
    }
}
