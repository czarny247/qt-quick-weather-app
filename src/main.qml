import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQml 2.14
import QtQuick.Layouts 1.14
import QtQml.Models 2.14
import QtQuick.Dialogs 1.3
import Qt.WeatherApiHandler 1.0
import SharedEnums.TemperatureType 1.0
import SharedEnums.TemperatureScale 1.0
import Qt.ScaleProperties 1.0
import QtPositioning 5.11

ApplicationWindow {
	id: window
	visible: true
	minimumWidth: weather_layout.width + errorUserFeedback.width
	minimumHeight: weather_layout.height + errorUserFeedback.height + overlayHeader.height
	width: Screen.desktopAvailableWidth
	height: Screen.desktopAvailableHeight

    GPSComponent {
    	id: gps
    }

    OverlayHeader {
    	id: overlayHeader
    }

	HamburgerMenu {
		id: hamburgerMenu
	}

	MouseArea {
		anchors.fill: parent
		id: main_mouse_area

		//todo: add disclaimer if api key is incorrect
		//check api key by fetching data

		GridLayout
		{
			anchors.centerIn: parent
			anchors.verticalCenterOffset: overlayHeader.height
			id: weather_layout
			columns: 1
			visible: false
			CurrentWeatherInputLayout {
				id: current_weather_input_layout

				Connections {
					target: current_weather_button
					onWeatherUpdated: current_weather_input_layout.visible = false
				}

				CurrentWeatherButton {
					id: current_weather_button
				}
			}

			ErrorUserFeedbackTextArea {
				id: errorUserFeedback
			}

			CurrentWeatherOutputLayout {}
		}

		GridLayout
		{
			anchors.centerIn: parent
			anchors.verticalCenterOffset: overlayHeader.height
			id: current_location_layout
			columns: 1
			visible: true	
			CurrentLocationWeatherOutputLayout {}	
		}
	}
}