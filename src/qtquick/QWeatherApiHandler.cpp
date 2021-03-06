#include "QWeatherApiHandler.hpp"

#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <QObject>
#include <QMetaObject>
#include <QQmlComponent>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>

#include <cassert>
#include <utility>

#include "backend/BuildType.hpp"

namespace qtquick
{

void QWeatherApiHandler::dataFetched(QNetworkReply* reply)
{
	QString strReply = (QString)reply->readAll();
    
    //todo: make logger class
    if(isDebug())
    {
    	qDebug() << "Response:" << strReply;
    }

    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
	QJsonObject jsonObj = jsonResponse.object();
	data_.reset(new backend::WeatherApiResponseData(jsonObj));
	this->fetchDataFinishedCallback();
}

QWeatherApiHandler::QWeatherApiHandler(std::shared_ptr<backend::WeatherApiHandler> weatherApiHandler)
: weatherApiHandler_(weatherApiHandler)
{
	weatherApiHandler_->setFetchDataFinishedCallback(
		std::bind(&QWeatherApiHandler::fetchDataFinishedCallback, this));
}

Q_INVOKABLE void QWeatherApiHandler::getData(const QString& zipCode, 
	const QString& countryCode)
{
	QNetworkAccessManager* network = new QNetworkAccessManager(this);
	connect(network, &QNetworkAccessManager::finished, this, &QWeatherApiHandler::dataFetched);
	const QUrl url = QUrl(QString::fromStdString(weatherApiHandler_->getRequestUrlZipCountry(
		zipCode.toStdString(), countryCode.toStdString())));
	QNetworkRequest req(url);
	network->get(req);
}

Q_INVOKABLE void QWeatherApiHandler::getData(const QGeoCoordinate& coords)
{
	QNetworkAccessManager* network = new QNetworkAccessManager(this);
	connect(network, &QNetworkAccessManager::finished, this, &QWeatherApiHandler::dataFetched);
	const QUrl url = QUrl(QString::fromStdString(weatherApiHandler_->getRequestUrlGPS(
		{coords.latitude(), coords.longitude()})));
	QNetworkRequest req(url);
	network->get(req);
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

Q_INVOKABLE bool QWeatherApiHandler::isDebug()
{
	return getBuildType() == "Debug";
}

void QWeatherApiHandler::fetchDataFinishedCallback()
{
	emit fetchDataFinished();
}

}