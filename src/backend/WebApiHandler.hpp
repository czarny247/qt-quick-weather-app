#pragma once

#include <string>
#include <cpprest/json.h>
#include <cpprest/http_client.h>

#include "backend/GPSCoordinates.hpp"

namespace backend
{

class WebApiHandler
{

public:
	WebApiHandler(std::string&& clientUrl, std::string&& requestUriPrefix);
	~WebApiHandler() = default;

	WebApiHandler(const WebApiHandler&) = delete;
	WebApiHandler& operator=(const WebApiHandler&) = delete;

	void setApiKey(const std::string& apiKey);
	pplx::task<web::json::value> fetchData(const std::string& zipCode, const std::string& countryCode);
	pplx::task<web::json::value> fetchData(const GPSCoordinates& coords);


private:
	const std::string clientUrl_ {};
	const std::string requestUriPrefix_ {};
	std::string apiKey_ {};
};

}