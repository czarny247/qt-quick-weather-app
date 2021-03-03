#include "QWeatherApiHandler.hpp"

#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <QObject>
#include <QMetaObject>
#include <QQmlComponent>

#include <cassert>
#include <utility>

namespace qtquick
{

QWeatherApiHandler::QWeatherApiHandler(std::shared_ptr<backend::WeatherApiHandler> weatherApiHandler)
: weatherApiHandler_(weatherApiHandler)
{
	weatherApiHandler_->setFetchDataFinishedCallback(
		std::bind(&QWeatherApiHandler::fetchDataFinishedCallback, this));
}

Q_INVOKABLE void QWeatherApiHandler::fetchData(const QString& zipCode, 
	const QString& countryCode)
{
	data_.reset(weatherApiHandler_->fetchData(zipCode.toStdString(), countryCode.toStdString()));
}

Q_INVOKABLE void QWeatherApiHandler::fetchData(const QGeoCoordinate& coords)
{
	data_.reset(weatherApiHandler_->fetchData({coords.latitude(), coords.longitude()}));
}

Q_INVOKABLE int QWeatherApiHandler::responseStatusCode()
{
	assert(data_ != nullptr);
	return data_->responseStatusCode();
}

Q_INVOKABLE QString QWeatherApiHandler::responseStatusInfo()
{
	assert(data_ != nullptr);
	return QString::fromStdString(data_->responseStatusInfo());
}

Q_INVOKABLE QString QWeatherApiHandler::responseStatusUserFeedback()
{
	assert(data_ != nullptr);
	return QString::fromStdString(data_->responseStatusUserFeedback());
}

Q_INVOKABLE QString QWeatherApiHandler::cityName(bool withCountryCode)
{
	assert(data_ != nullptr);
	return QString::fromStdString(data_->cityName(withCountryCode));
}

Q_INVOKABLE QString QWeatherApiHandler::temperature(int temperatureType, int temperatureScale)
{
	return temperature(static_cast<TemperatureType>(temperatureType),
		static_cast<TemperatureScale>(temperatureScale));
}

QString QWeatherApiHandler::temperature(TemperatureType type, TemperatureScale scale)
{
	assert(data_ != nullptr);
	return QString::fromStdString(data_->temperature(type, scale)) 
		+ temperature_scale::temperatureUnit(scale);
}

Q_INVOKABLE bool QWeatherApiHandler::isUriValid()
{
	return weatherApiHandler_->isUriValid();
}

void QWeatherApiHandler::fetchDataFinishedCallback()
{
	emit fetchDataFinished();
}

}