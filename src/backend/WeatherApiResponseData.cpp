#include "WeatherApiResponseData.hpp"

#include "3party/HttpStatusCodes_C++11.h"

#include <iostream>

#include <string>
#include <cmath>

namespace
{

std::string responseStatusUserFeedback(HttpStatus::Code code)
{
	switch(code)
	{

	case HttpStatus::Code::Unauthorized:
		return "Please provide valid API key.";
	case HttpStatus::Code::NotFound:
		return "Please provide valid zip code and country code.";
	default:
		return "User feedback: none.";
	}
}


}

namespace backend
{

WeatherApiResponseData::WeatherApiResponseData(web::json::value& weatherApiResponseBody)
: weatherApiResponseBody_(weatherApiResponseBody)
{
}

unsigned int WeatherApiResponseData::responseStatusCode()
{
	int result {0};

	try
	{
		if(weatherApiResponseBody_["cod"].is_string())
		{
			result = std::stoi(weatherApiResponseBody_["cod"].as_string());
		}

		if(weatherApiResponseBody_["cod"].is_integer())
		{
			result = weatherApiResponseBody_["cod"].as_integer();
		}
	}
	catch(const web::json::json_exception& e)
	{
		result = 0;
	}

	return result;
}

//handle null jsons

std::string WeatherApiResponseData::responseStatusInfo()
{
	int code = responseStatusCode();
	std::string reasonPhrase = HttpStatus::reasonPhrase(code);
	return {std::to_string(code) + ": " + reasonPhrase + ". " 
		+ responseStatusUserFeedback(static_cast<HttpStatus::Code>(code))};
}

std::string WeatherApiResponseData::cityName(bool withCountryCode)
{
	std::string result {""};

	try
	{
		result = weatherApiResponseBody_["name"].as_string() + (withCountryCode 
			? std::string(", ").append(weatherApiResponseBody_["sys"]["country"].as_string())
			: "");
	}
	catch(const web::json::json_exception& e)
	{
		//todo: print to console in debug mode
		result = "-";
	}

	return result;
}

std::string WeatherApiResponseData::temperature(TemperatureType type, TemperatureScale scale)
{
	std::string result {""};

	try
	{
		auto temperatures = weatherApiResponseBody_["main"];
		double temperature =
			[](auto& temps, TemperatureType type) -> double
			{
				try
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
				}
				catch(const web::json::json_exception& e)
				{
					throw e;
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
	
		result = std::to_string(static_cast<int>(std::round(convertTempByScale(temperature, scale))));

	}
	catch(const web::json::json_exception& e)
	{
		//todo: print to console in debug mode
		result = "-";
	}

	return result;
}

// std::string WeatherApiResponseData::weatherInfo()
// {

// }

// std::string WeatherApiResponseData::windInfo()
// {

// }

}