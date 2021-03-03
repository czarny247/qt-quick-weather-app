import Qt.WeatherApiHandler 1.0
import QtQml 2.14
import QtQuick.Controls 2.14

Button {
	text: "CURRENT WEATHER"

	signal weatherUpdated

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
						// current_weather_output_layout.cityName.text = OpenWeatherMapApi.cityName(true)
						// current_weather_output_layout.temperature.text = OpenWeatherMapApi.temperature(
						// 	TemperatureType.Average, 
						// 	TemperatureScale.Celsius)
						// errorUserFeedback.visible = false
						// weather_input_layout.visible = false
						// current_weather_output_layout.visible = false
						// current_weather_output_layout.visible = true
						weatherUpdated()
					}
				}
			}
		}
	}

	onClicked: {
		OpenWeatherMapApi.fetchData(zip_code.text, country_code.text)
	}
}