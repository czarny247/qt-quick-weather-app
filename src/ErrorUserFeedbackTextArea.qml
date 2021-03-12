import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.WeatherApiHandler 1.0
import QtQml 2.14

TextArea {
	id: errorUserFeedback
	visible: OpenWeatherMapApi.isDebug()
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