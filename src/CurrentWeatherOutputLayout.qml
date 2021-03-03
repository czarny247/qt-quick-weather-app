import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.WeatherApiHandler 1.0
import SharedEnums.TemperatureType 1.0
import SharedEnums.TemperatureScale 1.0

ColumnLayout {
	id: weather_output_layout
	visible: false

	function updateCityAndTemperature()
	{
		cityName.text = OpenWeatherMapApi.cityName(true)
		temperature.text = OpenWeatherMapApi.temperature(TemperatureType.Average, TemperatureScale.Celsius)
		current_weather_output_layout.visible = false
		current_weather_output_layout.visible = true
	}

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
	ResetWeatherButton {}
	RefreshWeatherButton {}
}