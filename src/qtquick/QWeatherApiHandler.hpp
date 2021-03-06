#pragma once

#include <QGeoCoordinate>
#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QQmlApplicationEngine>
#include "backend/WeatherApiHandler.hpp"
#include "backend/WeatherApiResponseData.hpp"
#include "utils/shared_enums/TemperatureScale.hpp"
#include "utils/shared_enums/TemperatureType.hpp"
#include <memory>
#include <functional>

#include <QNetworkReply>

using TemperatureType = temperature_type::TemperatureType;
using TemperatureScale = temperature_scale::TemperatureScale;

namespace qtquick
{

class QWeatherApiHandler : public QObject
{
	Q_OBJECT
public:
	QWeatherApiHandler(std::shared_ptr<backend::WeatherApiHandler> weatherApiHandler);

	~QWeatherApiHandler() = default;

	Q_INVOKABLE void getData(const QString& zipCode, 
		const QString& countryCode);

	Q_INVOKABLE void getData(const QGeoCoordinate& coords);

	Q_INVOKABLE int responseStatusCode();
	Q_INVOKABLE QString responseStatusInfo();
	Q_INVOKABLE QString responseStatusUserFeedback();
	Q_INVOKABLE QString cityName(bool withCountryCode);
	Q_INVOKABLE QString temperature(int temperatureType, int temperatureScale);
	Q_INVOKABLE bool isUriValid();

	//move to another class
	Q_INVOKABLE bool isDebug();

	void fetchDataFinishedCallback();

private:
	std::shared_ptr<backend::WeatherApiHandler> weatherApiHandler_ {nullptr};
	std::unique_ptr<backend::WeatherApiResponseData> data_ {nullptr};

	//workaround - see: https://bugreports.qt.io/browse/QTBUG-19741
	QString temperature(TemperatureType type, TemperatureScale scale);

signals:
	void fetchDataFinished();

private slots:
	void dataFetched(QNetworkReply*);
};

}