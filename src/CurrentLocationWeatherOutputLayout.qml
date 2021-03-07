import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.WeatherApiHandler 1.0
import QtQml 2.14
import SharedEnums.TemperatureType 1.0
import SharedEnums.TemperatureScale 1.0

WeatherOutputLayout {
	visible: true
	
	Connections {
		target: OpenWeatherMapApi
		onFetchDataFinished : {
			cityName.text = OpenWeatherMapApi.cityName(true)
			temperature.text = OpenWeatherMapApi.temperature(TemperatureType.Average,
					TemperatureScale.Celsius)
		}
	}

}