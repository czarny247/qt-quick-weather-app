pragma Singleton
import QtQuick 2.0
import QtQuick.Window 2.14

QtObject
{
    id: root

    readonly property real referenceScreenWidth: 1280
    readonly property real referenceScreenHeight: 800

    readonly property real screenHeight: Screen.desktopAvailableHeight
    readonly property real screenWidth: Screen.desktopAvailableWidth

    function horizontal_scale(size) {
        return Math.round(size * (screenWidth / referenceScreenWidth))
    }

    function vertical_scale(size) {
        return Math.round(size * (screenHeight / referenceScreenHeight))
    }

    function text_scale(size) {
        return Math.round((horizontal_scale(size) + vertical_scale(size)) / 2)
    }

    readonly property int textSizeNormal: text_scale(42)
    readonly property int textSizeSmall: text_scale(32)

    // readonly property real screenLeftMargin: hscale(16)
    // readonly property real screenRightMargin: screenLeftMargin
    // readonly property real statusBarHeight: vscale(79)
    // readonly property real mainPageHeight: vscale(599)
    // readonly property real appToolBarHeight: vscale(120)
    // readonly property real dividerSize: 1

    // readonly property int textSizeNormal: tscale(42)
    // readonly property int textSizeSmall: tscale(32)
    // readonly property int textSizeVerySmall: tscale(24)
    // readonly property color textColorNormal: "#ffec8b" // lightgoldenrod 1
    // readonly property color textColorSmall: "#cdbe70" // lightgoldenrod 3
    // readonly property color textColorSelected: "#7FFF00" // chartreuse

    // readonly property real leftTabButtonWidth: hscale(319)
    // readonly property real leftTabButtonHeight: vscale(99)
    // readonly property real toolButtonWidth: hscale(191)
    // readonly property real toolButtonHeight: vscale(99)
    // readonly property int buttonBorderWidth: 2

    // readonly property real songInfoWidth: hscale(860)
    // readonly property real songInfoHeight: vscale(300)
    // readonly property real songInfoTextFieldWidth: hscale(510)
    // readonly property int songInfoTextSpacing: vscale(16)
    // readonly property real songInfoCoverSize: hscale(300)

    // readonly property real songProgressBarWidth: hscale(576)
    // readonly property real songProgressBarHeight: vscale(49)
    // readonly property real songProgressBarMargin: hscale(3)
    // readonly property real songProgressBarTextMargin: hscale(12)
}