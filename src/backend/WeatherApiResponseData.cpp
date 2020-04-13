#include "WeatherApiResponseData.hpp"

#include "3party/HttpStatusCodes_C++11.h"

#include <cmath>

namespace backend
{

WeatherApiResponseData::WeatherApiResponseData(web::json::value& weatherApiResponseBody)
: weatherApiResponseBody_(weatherApiResponseBody)
{
}

unsigned int WeatherApiResponseData::responseStatusCode()
{
	return weatherApiResponseBody_["cod"].as_integer();
}

//handle null jsons

std::string WeatherApiResponseData::responseStatusInfo()
{
	int code = responseStatusCode();
	std::string reasonPhrase = HttpStatus::reasonPhrase(code);
	return {std::to_string(code) + ": " + reasonPhrase};
}

std::string WeatherApiResponseData::cityName(bool withCountryCode)
{
	return weatherApiResponseBody_["name"].as_string() + 
		(withCountryCode 
			? std::string(", ").append(weatherApiResponseBody_["sys"]["country"].as_string())
			: "");
}

std::string WeatherApiResponseData::temperature(TemperatureType type, TemperatureScale scale)
{
	auto temperatures = weatherApiResponseBody_["main"];
	double temperature =
		[](auto& temps, TemperatureType type) -> double
		{
			switch(type)
			{
			case TemperatureType::Average:
				return temps["temp"].as_double();
			case TemperatureType::Max:
				return temps["temp_max"].as_double();
			case TemperatureType::Min:
				return temps["temp_min"].as_double();
			case TemperatureType::FeelsLike:
				return temps["feels_like"].as_double();
			default:
				return 0.0; //?
			}
		}(temperatures, type);

	auto convertTempByScale =
		[](double temperature, TemperatureScale scale) -> double
		{
			switch(scale)
			{
			case TemperatureScale::Kelvin:
				return temperature; //because api provides temperature in Kelvins
			case TemperatureScale::Celsius:
			{
				static constexpr double celsiusOffset {273.15};
				return temperature - celsiusOffset;
			}
			case TemperatureScale::Fahrenheit:
			{
				static constexpr double fahrenheitOffset {459.67};
				static constexpr double fahrenheitFactor {9.0/5.0};
				return temperature * fahrenheitFactor - fahrenheitOffset;
			}

			default:
				return temperature;
			}
		};

	return std::to_string(static_cast<int>(std::round(convertTempByScale(temperature, scale))));
}

// std::string WeatherApiResponseData::weatherInfo()
// {

// }

// std::string WeatherApiResponseData::windInfo()
// {

// }

}