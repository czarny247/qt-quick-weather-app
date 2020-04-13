#pragma once

#include <string>
#include <cpprest/json.h>
#include <cpprest/http_client.h>

#include "backend/GPSCoordinates.hpp"
#include "backend/WeatherApiResponseData.hpp"

namespace backend
{

class WeatherApiHandler
{

public:
	WeatherApiHandler(std::string&& clientUrl, std::string&& requestUriPrefix);
	~WeatherApiHandler() = default;

	WeatherApiHandler(const WeatherApiHandler&) = delete;
	WeatherApiHandler& operator=(const WeatherApiHandler&) = delete;

	void setApiKey(const std::string& apiKey);
	WeatherApiResponseData* fetchData(const std::string& zipCode, const std::string& countryCode);
	WeatherApiResponseData* fetchData(const GPSCoordinates& coords);


private:
	const std::string clientUrl_ {};
	const std::string requestUriPrefix_ {};
	std::string apiKey_ {};
};

}