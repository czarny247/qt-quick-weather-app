import Qt.WeatherApiHandler 1.0
import QtQml 2.14
import QtQuick.Controls 2.14

Button {
	text: "CURRENT WEATHER"

	signal weatherUpdated

	//todo all of these logic shouldn't be in button
	//todo button should only send on clicked and that's all
	//todo firstly refactor it to functions
	//signal uriValidationFailed

	Connections {
		target: OpenWeatherMapApi

		onFetchDataFinished : {
			if(weather_layout.visible == true)
			{
				if(!OpenWeatherMapApi.isUriValid())
				{
					errorUserFeedback.updateText("Please provide valid country code and zip code.", "red")
					current_weather_input_layout.zip_code = ""
					current_weather_input_layout.country_code = ""
				}
				else
				{
					var responseStatus = OpenWeatherMapApi.responseStatusCode()
					if(responseStatus != 200) //todo: use type from backend rather than int
					{
						errorUserFeedback.updateText(OpenWeatherMapApi.responseStatusInfo(), "red")
						if(responseStatus == 404)
						{
							current_weather_input_layout.zip_code = ""
							current_weather_input_layout.country_code = ""
						}
					}
					else
					{
						weatherUpdated()
					}
				}
			}
		}
	}

	onClicked: {
		OpenWeatherMapApi.getData(current_weather_input_layout.zip_code, 
			current_weather_input_layout.country_code)
	}
}