import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQml 2.14
import QtQuick.Layouts 1.14
import QtQml.Models 2.14
import Qt.WeatherApiHandler 1.0
import SharedEnums.TemperatureType 1.0
import SharedEnums.TemperatureScale 1.0

ApplicationWindow {
	id: window
	visible: true
	minimumWidth: weather_layout.width + errorUserFeedback.width
	minimumHeight: weather_layout.height + errorUserFeedback.height + overlayHeader.height

	ToolBar {
		id: overlayHeader
		z: 1
		width: parent.width
		parent: window.overlay

		RowLayout {
			ToolButton {
				Layout.alignment: Qt.AlignLeft
				id: hamburgerButton
				property var hamburgerMenuVisible: false
				text: qsTr("H")
				onClicked: hamburgerMenuVisible = !hamburgerMenuVisible
			}

			ToolSeparator {
			}

			Label {
				id: label
				text: "Qt Quick Weather App"
			}
		}
	}

	Drawer {
		id: drawer
		y: overlayHeader.height
		width: window.width / 2
		height: window.height - overlayHeader.height
		visible: hamburgerButton.hamburgerMenuVisible

		ColumnLayout {
			width: parent.width
			Button {
				id: settingsButton
				Layout.preferredWidth: parent.width
				text: "Settings"
				onClicked: {
					set_api_key_layout.visible = true
					weather_layout.visible = false
				}
			}
			
			Button {
				id: weatherButton
				Layout.preferredWidth: parent.width
				text: "Weather"
				onClicked: {
					set_api_key_layout.visible = false
					weather_layout.visible = true
				}
			}
		}
	}

	MouseArea {
		anchors.fill: parent

		RowLayout {
			anchors.centerIn: parent
			y: overlayHeader.height
			id: set_api_key_layout
			visible: true

			TextField {
				id: set_api_key_text
				placeholderText: qsTr("Enter api key")
				echoMode: TextInput.Password
				onPressed : {
					text = ""
					color = "black"
					echoMode = TextInput.Password
				}
			}
			Button {
				id: set_api_key_button
				text: "SET"

				Connections {
					target: OpenWeatherMapApi
					onFetchDataFinished : {
						var responseStatus = OpenWeatherMapApi.responseStatusCode()
						if(responseStatus == 401) {
							set_api_key_text.text = OpenWeatherMapApi.responseStatusUserFeedback()
							set_api_key_text.color = "red"
							set_api_key_text.echoMode = TextInput.Normal
							set_api_key_text.width = set_api_key_text.contentWidth
						}
						else
						{
							set_api_key_layout.visible = false
							weather_layout.visible = true
						}
					}
				}

				onClicked: {
					OpenWeatherMapApi.setApiKey(set_api_key_text.text)
					OpenWeatherMapApi.fetchData("0", "0") //just call to check if api key is valid
				}
			}
		}

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
				text: "sth" //change placeholder text and add label for this text area - wrap it in row layout
				function updateText(text, color)
				{
					errorUserFeedback.text = text
					errorUserFeedback.color = color
				}
			}
			ColumnLayout {
				//anchors.centerIn: parent
				//anchors.verticalCenterOffset: overlayHeader.height
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
						sendbutton.visible = true

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