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
	//minimumWidth: grid_main.width + json_text.width + overlayHeader.width
	//minimumHeight: grid_main.height + json_text.height + overlayHeader.height

    ToolBar {
        id: overlayHeader

        z: 1
        width: parent.width
        parent: window.overlay

        ToolButton {
        	id: hamburgerButton
        	property var hamburgerMenuVisible: false
        	text: qsTr("H")
        	onClicked: hamburgerMenuVisible = !hamburgerMenuVisible
        }

        Label {
            id: label
            anchors.centerIn: parent
            text: "Qt Quick Weather App"
        }
    }

    Drawer {
        id: drawer
        y: overlayHeader.height
        width: window.width / 2
        height: window.height - overlayHeader.height
        visible: hamburgerButton.hamburgerMenuVisible

        Label {
            text: "Content goes here!"
            anchors.centerIn: parent
        }
    }

	MouseArea {
		anchors.fill: parent

		GridLayout
		{
			y: overlayHeader.height
			id: grid_main
			columns: 1
			GridLayout
			{
				id: grid_sub
				columns: 2

				GridLayout {
					id: grid_text
					columns: 1

					TextField {
						id: api_key
						placeholderText: qsTr("Enter api key")
						echoMode: TextInput.Password
					}

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
					id: sendbutton
					text: "SEND"

					Connections {
						target: OpenWeatherMapApi
						onFetchDataFinished : {
							console.log("Fetch data finished")
							if(!OpenWeatherMapApi.isUriValid())
							{
								json_text.updateText("Please provide valid country code and zip code.")
								zip_code.text = ""
								country_code.text = ""
							}
							else
							{
								var responseStatus = OpenWeatherMapApi.responseStatusCode()
								if(responseStatus != 200) //use type from backend rather than ints
								{
									json_text.updateText(OpenWeatherMapApi.responseStatusInfo())
									if(responseStatus == 401)
									{
										api_key.text = ""
									}
									if(responseStatus == 404)
									{
										zip_code.text = ""
										country_code.text = ""
									}
								}
								else
								{
									json_text.updateText(OpenWeatherMapApi.cityName(true) + " " 
										+ OpenWeatherMapApi.temperature(TemperatureType.Average, 
											TemperatureScale.Celsius))
								}
							}
						}
					}

					onClicked: {
						OpenWeatherMapApi.setApiKey(api_key.text)
						OpenWeatherMapApi.fetchData(zip_code.text, country_code.text)
						//provide info
					}
				}
			}
			TextArea {
				id: json_text
				text: "sth"
				function updateText(txt)
				{
					json_text.text = txt
				}
			}
		}
	}
}