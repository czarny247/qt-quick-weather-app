import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Drawer {
	y: overlayHeader.height
	width: window.width * 0.5
	height: window.height - overlayHeader.height
	visible: false

	ColumnLayout {
		width: parent.width
		
		Button {
			visible: true
			Layout.preferredWidth: parent.width
			text: "Weather in current location"
			onClicked: {
				weather_layout.visible = false
				current_location_layout.visible = true
			}
		}

		Button {
			visible: true
			Layout.preferredWidth: parent.width
			text: "Weather in different city"
			onClicked: {
				weather_layout.visible = true
				current_location_layout.visible = false
			}
		}
	}
}