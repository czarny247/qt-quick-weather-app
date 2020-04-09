import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQml 2.14
import QtQuick.Layouts 1.14
import QtQml.Models 2.14
import Qt.WebApiHandler 1.0

Window {
	id: main_window
	visible: true
	MouseArea {
		anchors.fill: parent

		GridLayout
		{
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
					onClicked: {
						OpenWeatherMapApi.setApiKey(api_key.text)
						OpenWeatherMapApi.fetchData(zip_code.text, country_code.text)
						json_text.updateText(OpenWeatherMapApi.getLastFetchedData())
					}
				}
			}
			TextArea {
				id: json_text
				text: "sth"
				function updateText(txt)
				{
					console.log("txt is", txt)
					json_text.text = txt
				}
			}
		}
	}
}