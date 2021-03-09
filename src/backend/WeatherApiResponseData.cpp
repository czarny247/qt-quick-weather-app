#include "WeatherApiResponseData.hpp"

#include "3party/HttpStatusCodes_C++11.h"

#include <iostream>

#include <optional>
#include <string>
#include <cmath>

#include <QJsonValue>

namespace
{

std::string userFeedback(HttpStatus::Code code)
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

bool isTemperatureAvailable(const QJsonObject& obj)
{
	if(!obj.contains("main"))
	{
		return false;
	}
	else
	{
		auto mainObj = obj["main"].toObject();

		if(!mainObj.contains("temp")
			|| !mainObj.contains("temp_max")
			|| !mainObj.contains("temp_min")
			|| !mainObj.contains("feels_like"))
		{
			return false;
		}
	}

	return true;
}

std::optional<double> extractTemperature(const QJsonObject& obj, const std::string& tempKey)
{
	return obj[tempKey.c_str()].isDouble() 
		? std::optional<double>(obj[tempKey.c_str()].toDouble())
		: std::nullopt;
}

}

namespace backend
{

WeatherApiResponseData::WeatherApiResponseData(QJsonObject& weatherApiResponseBody)
: weatherApiResponseBody_(weatherApiResponseBody)
{
}

unsigned int WeatherApiResponseData::responseStatusCode()
{
	int result {0};

	auto it = weatherApiResponseBody_.find("cod");
	if(it != weatherApiResponseBody_.end())
	{
		result = it->toInt();
	}
	return result;
}

std::string WeatherApiResponseData::responseStatusInfo()
{
	int code = responseStatusCode();
	std::string reasonPhrase = HttpStatus::reasonPhrase(code);
	return {std::to_string(code) + ": " + reasonPhrase + ". " 
		+ userFeedback(static_cast<HttpStatus::Code>(code))};
}

std::string WeatherApiResponseData::responseStatusUserFeedback()
{
	return {userFeedback(static_cast<HttpStatus::Code>(responseStatusCode()))};
}

std::string WeatherApiResponseData::cityName(bool withCountryCode)
{
	std::string result {"-"};

	auto it = weatherApiResponseBody_.find("name");
	if(it != weatherApiResponseBody_.end())
	{
		result = it->toString().toStdString();

		it = weatherApiResponseBody_.find("country");
		if(it != weatherApiResponseBody_.end())
		{
			result.append(", ").append(it->toString().toStdString());
		}
	}
	return result;
}

std::string WeatherApiResponseData::temperature(TemperatureType type, TemperatureScale scale)
{
	std::string result {"-"};

	if (!isTemperatureAvailable(weatherApiResponseBody_))
	{
		return result;
	}

	std::optional<double> maybeTemperature = 
		[this](const auto& obj, TemperatureType type) -> std::optional<double>
		{
			switch(type)
			{
			case TemperatureType::Average:
				return extractTemperature(obj, "temp");
			case TemperatureType::Max:
				return extractTemperature(obj, "temp_max");
			case TemperatureType::Min:
				return extractTemperature(obj, "temp_min");
			case TemperatureType::FeelsLike:
				return extractTemperature(obj, "feels_like");
			default:
				return std::nullopt;
			}

		}(weatherApiResponseBody_["main"].toObject(), type);

	auto convertTempByScale =
		[](double temperature, TemperatureScale scale) -> double
		{
			switch(scale)
			{
			case TemperatureScale::Kelvin:
				return temperature;
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

	if(maybeTemperature.has_value())
	{
		return std::to_string(static_cast<int>(
			std::round(convertTempByScale(maybeTemperature.value(), scale))));
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