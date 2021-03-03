import Qt.ScaleProperties 1.0
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

ToolBar {
	z: 1
	width: window.width
	parent: window.overlay

	RowLayout {
		ToolButton {
			Layout.alignment: Qt.AlignLeft
			text: qsTr("☰")
			onClicked: {
				hamburgerMenu.visible = !hamburgerMenu.visible
			} 

		}

		ToolSeparator {
		}

		Label {
			id: label
			text: "Qt Quick Weather App"
			font.pixelSize: ScaleProperties.textSizeSmall
		}
	}
}