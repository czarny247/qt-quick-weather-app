import QtQuick.Controls 2.14

Button {
	text: "RESET"
	onClicked: {
		cityName.text = cityName.placeholderText
		temperature.text = temperature.placeholderText
		current_weather_output_layout.visible = false
		errorUserFeedback.visible = true
		weather_input_layout.visible = true
		current_weather_button.visible = true
		zip_code.text = ""
		country_code.text = ""
	}
}