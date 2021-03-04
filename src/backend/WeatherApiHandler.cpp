#include "backend/ApiKey.hpp"
#include "WeatherApiHandler.hpp"
#include <utility>

namespace backend
{

WeatherApiHandler::WeatherApiHandler(std::string&& clientUrl, std::string&& requestUriPrefix)
: clientUrl_(std::move(clientUrl))
, requestUriPrefix_(std::move(requestUriPrefix))
{

}

std::string WeatherApiHandler::getRequestUrlZipCountry(const std::string& zipCode, const std::string& countryCode)
{
	std::string uri {"/"};
	uri.append(requestUriPrefix_.c_str());
	uri.append("zip=");
	uri.append(zipCode.c_str());
	uri.append(",");
	uri.append(countryCode.c_str());
	uri.append("&appid=");
	uri.append(getApiKey().c_str());

	//todo validate uri
	isUriValid_ = true;

	return clientUrl_ + uri;
}

std::string WeatherApiHandler::getRequestUrlGPS(const GPSCoordinates& coords)
{
	std::string uri {"/"};
	uri.append(requestUriPrefix_.c_str());
	uri.append("lat=");
	uri.append(std::to_string(coords.latitude_).c_str());
	uri.append("&lon=");
	uri.append(std::to_string(coords.longitude_).c_str());
	uri.append("&appid=");
	uri.append(getApiKey().c_str());

	//todo validate uri
	isUriValid_ = true;

	return clientUrl_ + uri;
}

bool WeatherApiHandler::isUriValid()
{
	return isUriValid_;
}

void WeatherApiHandler::setFetchDataFinishedCallback(std::function<void(void)> callback)
{
	fetchDataFinishedCallback_ = callback;
}

}