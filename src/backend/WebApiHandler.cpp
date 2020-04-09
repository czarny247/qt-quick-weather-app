#include "WebApiHandler.hpp"
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <utility>

using namespace concurrency::streams;
using namespace utility;
using namespace web::http::client;
using namespace web::http;
using namespace web::json;
using namespace web;

namespace
{

pplx::task<json::value> fetchDataImpl(const std::string& requestUri, const std::string& clientUrl)
{
	http_client weatherClient(U(clientUrl.c_str()));

	return weatherClient.request(methods::GET, requestUri)
		.then([](http_response resp)
		{
			//todo: handle all status codes
			printf("Received response status code:%u\n", resp.status_code());
			return resp.extract_json();
		});
}

}

namespace backend
{

WebApiHandler::WebApiHandler(std::string&& clientUrl, std::string&& requestUriPrefix)
: clientUrl_(std::move(clientUrl))
, requestUriPrefix_(std::move(requestUriPrefix))
{

}

void WebApiHandler::setApiKey(const std::string& apiKey)
{
	apiKey_ = apiKey;
}

pplx::task<json::value> WebApiHandler::fetchData(const std::string& zipCode, const std::string& countryCode)
{
	//todo: create query builder
	std::string query {"/"};
	query.append(requestUriPrefix_.c_str());
	query.append("zip=");
	query.append(zipCode.c_str());
	query.append(",");
	query.append(countryCode.c_str());
	query.append("&appid=");
	query.append(apiKey_.c_str());

    std::cout << "query: " << query << std::endl;

    return fetchDataImpl(query, clientUrl_);
}

pplx::task<json::value> WebApiHandler::fetchData(const GPSCoordinates& coords)
{
    uri_builder builder(U(requestUriPrefix_));
    builder.append_query(U("lat"), U(std::to_string(coords.latitude_).c_str()));
    builder.append_query(U("&lon"), U(std::to_string(coords.longitude_).c_str()), false);
    builder.append_query(U("&appid"), U(apiKey_.c_str()), false);

    std::cout << "query: " << builder.to_string() << std::endl;

	return fetchDataImpl(builder.to_string(), clientUrl_);
}

}