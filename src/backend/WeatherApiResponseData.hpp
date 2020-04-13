#pragma once

#include <string>
#include <cpprest/json.h>

#include "utils/shared_enums/TemperatureScale.hpp"
#include "utils/shared_enums/TemperatureType.hpp"

using TemperatureType = temperature_type::TemperatureType;
using TemperatureScale = temperature_scale::TemperatureScale;

namespace backend
{

class WeatherApiResponseData
{

public:
	WeatherApiResponseData(web::json::value& weatherApiResponseBody);
	WeatherApiResponseData(const WeatherApiResponseData&) = default;
	WeatherApiResponseData& operator=(const WeatherApiResponseData&) = default;

	unsigned int responseStatusCode();
	std::string responseStatusInfo();
	std::string cityName(bool withCountryCode);
	std::string temperature(TemperatureType type, TemperatureScale scale);

private:
	web::json::value weatherApiResponseBody_;

};

}