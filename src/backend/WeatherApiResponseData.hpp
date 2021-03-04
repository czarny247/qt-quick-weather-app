#pragma once

#include <string>
#include <QJsonObject>

#include "utils/shared_enums/TemperatureScale.hpp"
#include "utils/shared_enums/TemperatureType.hpp"

using TemperatureType = temperature_type::TemperatureType;
using TemperatureScale = temperature_scale::TemperatureScale;

namespace backend
{

class WeatherApiResponseData
{

public:
	WeatherApiResponseData(QJsonObject& weatherApiResponseBody);
	WeatherApiResponseData(const WeatherApiResponseData&) = default;
	WeatherApiResponseData& operator=(const WeatherApiResponseData&) = default;

	unsigned int responseStatusCodeQ();
	std::string responseStatusInfoQ();
	std::string responseStatusUserFeedbackQ();
	std::string cityNameQ(bool withCountryCode);
	std::string temperatureQ(TemperatureType type, TemperatureScale scale);

private:
	QJsonObject weatherApiResponseBodyQ_;

};

}