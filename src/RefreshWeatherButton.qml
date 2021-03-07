import SharedEnums.TemperatureType 1.0
import SharedEnums.TemperatureScale 1.0
import Qt.WeatherApiHandler 1.0
import QtQml 2.14
import QtQuick.Controls 2.14

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
		OpenWeatherMapApi.getData(current_weather_input_layout.zip_code, 
			current_weather_input_layout.country_code)
	}
}