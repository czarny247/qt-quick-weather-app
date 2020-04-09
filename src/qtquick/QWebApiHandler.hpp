#pragma once

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QQmlApplicationEngine>
#include "backend/WebApiHandler.hpp"
#include <memory>

namespace qtquick
{

class QWebApiHandler : public QObject
{
	Q_OBJECT
public:
	QWebApiHandler(std::shared_ptr<backend::WebApiHandler> webApiHandler)
	: webApiHandler_(webApiHandler)
	{}

	~QWebApiHandler() = default;

	Q_INVOKABLE void setApiKey(const QString& apiKey);
	Q_INVOKABLE void fetchData(const QString& zipCode, const QString& countryCode);
	Q_INVOKABLE QString getLastFetchedData(); //todo: change to QJsonObject

private:
	std::shared_ptr<backend::WebApiHandler> webApiHandler_;
	QString fetchedData_;

};

}