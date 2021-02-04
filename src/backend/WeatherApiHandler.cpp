#include "backend/ApiKey.hpp"
#include "WeatherApiHandler.hpp"
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/base_uri.h>
#include <utility>

using namespace concurrency::streams;
using namespace utility;
using namespace web::http::client;
using namespace web::http;
using namespace web::json;
using namespace web;

namespace backend
{

WeatherApiHandler::WeatherApiHandler(std::string&& clientUrl, std::string&& requestUriPrefix)
: clientUrl_(std::move(clientUrl))
, requestUriPrefix_(std::move(requestUriPrefix))
{

}

WeatherApiResponseData* WeatherApiHandler::fetchData(const std::string& zipCode, const std::string& countryCode)
{
	if(zipCode.empty() || countryCode.empty())
	{
		isUriValid_ = false;
		fetchDataFinishedCallback_();
		return nullptr;
	}

	std::string uri {"/"};
	uri.append(requestUriPrefix_.c_str());
	uri.append("zip=");
	uri.append(zipCode.c_str());
	uri.append(",");
	uri.append(countryCode.c_str());
	uri.append("&appid=");
	uri.append(getApiKey().c_str());

	if(!web::uri::validate(uri))
	{
		isUriValid_ = false;
		return nullptr;
	}

	WeatherApiResponseData* data = nullptr;

	try
	{
		auto json = fetchDataImpl(uri, clientUrl_).get();
		data = new WeatherApiResponseData(json);
	}
	catch(const pplx::invalid_operation& e)
	{
		data = nullptr;
	}

	return data;
}

WeatherApiResponseData* WeatherApiHandler::fetchData(const GPSCoordinates& coords)
{
	uri_builder builder(U(requestUriPrefix_));
	builder.append_query(U("lat"), U(std::to_string(coords.latitude_).c_str()));
	builder.append_query(U("&lon"), U(std::to_string(coords.longitude_).c_str()), false);
	builder.append_query(U("&appid"), U(getApiKey().c_str()), false);

	auto json = fetchDataImpl(builder.to_string(), clientUrl_).get();
	return new WeatherApiResponseData(json);
}

pplx::task<json::value> WeatherApiHandler::fetchDataImpl(const std::string& requestUri, 
	const std::string& clientUrl)
{
	http_client weatherClient(U(clientUrl.c_str()));

	return weatherClient.request(methods::GET, requestUri)
		.then([this](http_response resp)
		{
			//todo: handle all status codes
			isUriValid_ = true;
			printf("Received response status code:%u\n", resp.status_code());
			fetchDataFinishedCallback_();
			return resp.extract_json();
		});
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