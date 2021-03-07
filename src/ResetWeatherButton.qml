import QtQuick.Controls 2.14

Button {
	text: "RESET"
	onClicked: {
		cityName.text = cityName.placeholderText
		temperature.text = temperature.placeholderText
		current_weather_output_layout.visible = false
		errorUserFeedback.visible = true
		current_weather_input_layout.visible = true
		current_weather_button.visible = true
		current_weather_input_layout.zip_code = ""
		current_weather_input_layout.country_code = ""
	}
}