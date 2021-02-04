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

ApplicationWindow {
	id: window
	visible: true
	minimumWidth: weather_layout.width + errorUserFeedback.width
	minimumHeight: weather_layout.height + errorUserFeedback.height + overlayHeader.height
	width: Screen.desktopAvailableWidth
	height: Screen.desktopAvailableHeight

	ToolBar {
		id: overlayHeader
		z: 1
		width: window.width
		parent: window.overlay

		RowLayout {
			ToolButton {
				Layout.alignment: Qt.AlignLeft
				id: hamburgerButton
				property var hamburgerMenuVisible: false
				text: qsTr("☰")
				onClicked: {
					hamburgerMenuVisible = !hamburgerMenuVisible
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

	Drawer {
		id: drawer
		y: overlayHeader.height
		width: window.width * 0.5
		height: window.height - overlayHeader.height
		visible: hamburgerButton.hamburgerMenuVisible

		ColumnLayout {
			width: parent.width
			
			Button {
				id: weatherButton
				visible: true
				Layout.preferredWidth: parent.width
				text: "Weather"
				onClicked: {
					weather_layout.visible = true
				}
			}
		}
	}

	MouseArea {
		anchors.fill: parent
		id: main_mouse_area

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

				Button {
					id: weather_button
					text: "CURRENT WEATHER"

					Connections {
						target: OpenWeatherMapApi
						onFetchDataFinished : {
							if(weather_layout.visible == true)
							{
								if(!OpenWeatherMapApi.isUriValid())
								{
									errorUserFeedback.updateText("Please provide valid country code and zip code.", "red")
									zip_code.text = ""
									country_code.text = ""
								}
								else
								{
									var responseStatus = OpenWeatherMapApi.responseStatusCode()
									if(responseStatus != 200) //todo: use type from backend rather than int
									{
										errorUserFeedback.updateText(OpenWeatherMapApi.responseStatusInfo(), "red")
										if(responseStatus == 404)
										{
											zip_code.text = ""
											country_code.text = ""
										}
									}
									else
									{
										cityName.text = OpenWeatherMapApi.cityName(true)
										temperature.text = OpenWeatherMapApi.temperature(TemperatureType.Average, 
											TemperatureScale.Celsius)

										errorUserFeedback.visible = false
										weather_input_layout.visible = false
										weather_button.visible = false
										weather_output_layout.visible = true
									}
								}
							}
						}
					}

					onClicked: {
						OpenWeatherMapApi.fetchData(zip_code.text, country_code.text)
					}
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
			}
			ColumnLayout {
				id: weather_output_layout
				visible: false
				RowLayout {
					Label {
						text: "City:"
					}
					TextArea {
						id: cityName
						placeholderText: "CityName, CoutryCode"
					}
				}
				RowLayout {
					Label {
						text: "Temperature:"
					}
					TextArea {
						id: temperature
						placeholderText: "Temperature in Celsius"
					}
				}
				Button {
					text: "RESET"
					onClicked: {
						cityName.text = cityName.placeholderText
						temperature.text = temperature.placeholderText
						weather_output_layout.visible = false
						errorUserFeedback.visible = true
						weather_input_layout.visible = true
						weather_button.visible = true
						zip_code.text = ""
						country_code.text = ""

					}
				}

				Button {
					text: "REFRESH"
					Connections {
						target: OpenWeatherMapApi
						onFetchDataFinished : {
							cityName.text = OpenWeatherMapApi.cityName(true)
							temperature.text = OpenWeatherMapApi.temperature(TemperatureType.Average,
								TemperatureScale.Celsius)
						}
					}

					onClicked: {
						OpenWeatherMapApi.fetchData(zip_code.text, country_code.text)
					}
				}
			}
		}
	}
}