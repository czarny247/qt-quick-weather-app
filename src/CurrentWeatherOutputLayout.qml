import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.WeatherApiHandler 1.0
import QtQml 2.14
import SharedEnums.TemperatureType 1.0
import SharedEnums.TemperatureScale 1.0

WeatherOutputLayout {
	id: current_weather_output_layout
	visible: false

	function updateCityAndTemperature()
	{
		cityName.text = OpenWeatherMapApi.cityName(true)
		temperature.text = OpenWeatherMapApi.temperature(TemperatureType.Average, TemperatureScale.Celsius)
		current_weather_output_layout.visible = false
		current_weather_output_layout.visible = true
	}

	ResetWeatherButton {}
	RefreshWeatherButton {}
			
	Connections {
		target: current_weather_button
		onWeatherUpdated: current_weather_output_layout.updateCityAndTemperature()
	}
}