#pragma once

#include <string>
#include <functional>

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

	bool isUriValid();
	void setFetchDataFinishedCallback(std::function<void(void)> callback);

	std::string getRequestUrlZipCountry(const std::string& zipCode, const std::string& countryCode);
	std::string getRequestUrlGPS(const GPSCoordinates& coords);


private:
	const std::string clientUrl_ {};
	const std::string requestUriPrefix_ {};
	bool isUriValid_ {false};
	std::function<void(void)> fetchDataFinishedCallback_;
};

}