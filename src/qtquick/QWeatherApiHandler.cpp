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

Q_INVOKABLE void QWeatherApiHandler::setApiKey(const QString& apiKey)
{
	weatherApiHandler_->setApiKey(apiKey.toStdString());
}

Q_INVOKABLE void QWeatherApiHandler::fetchData(const QString& zipCode, 
	const QString& countryCode)
{
	data_.reset(weatherApiHandler_->fetchData(zipCode.toStdString(), countryCode.toStdString()));
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

}