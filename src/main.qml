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
			GridLayout {
				id: weather_input_layout
				columns: 2

				Connections {
					target: current_weather_button
					onWeatherUpdated: weather_input_layout.visible = false
				}

				GridLayout {
					id: grid_text
					columns: 1

					TextField {
						id: zip_code
						placeholderText: qsTr("Enter zip code")
					}

					TextField {
						id: country_code
						placeholderText: qsTr("Enter country code")
					}
				}

				CurrentWeatherButton {
					id: current_weather_button
				}
			}
			TextArea {
				id: errorUserFeedback
				placeholderText: "error feedback"
				function updateText(text, color)
				{
					errorUserFeedback.text = text
					errorUserFeedback.color = color
				}

				Connections {
					target: current_weather_button
					onWeatherUpdated: errorUserFeedback.visible = false
				}
			}

			CurrentWeatherOutputLayout {
				id: current_weather_output_layout
				Connections {
					target: current_weather_button
					onWeatherUpdated: current_weather_output_layout.updateCityAndTemperature()
				}
			}
		}

		GridLayout
		{
			anchors.centerIn: parent
			anchors.verticalCenterOffset: overlayHeader.height
			id: current_location_layout
			columns: 1
			visible: true

			ColumnLayout {
				id: current_location_weather_output_layout
				visible: true
				RowLayout {
					Label {
						text: "City:"
					}
					TextArea {
						id: current_location_cityName
						placeholderText: "CityName, CoutryCode"
					}
				}
				RowLayout {
					Label {
						text: "Temperature:"
					}
					TextArea {
						id: current_location_temperature
						placeholderText: "Temperature in Celsius"
					}
				}

				Connections {
					target: OpenWeatherMapApi
					onFetchDataFinished : {
						current_location_cityName.text = OpenWeatherMapApi.cityName(true)
						current_location_temperature.text = OpenWeatherMapApi.temperature(TemperatureType.Average,
								TemperatureScale.Celsius)
					}
				}
			}		
		}
	}
}