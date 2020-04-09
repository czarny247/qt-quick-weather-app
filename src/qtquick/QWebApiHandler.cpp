#include "QWebApiHandler.hpp"

#include <QJsonValue>
#include <QDebug>
#include <QObject>
#include <QMetaObject>
#include <QQmlComponent>

namespace qtquick
{

Q_INVOKABLE void QWebApiHandler::setApiKey(const QString& apiKey)
{
	webApiHandler_->setApiKey(apiKey.toStdString());
}

Q_INVOKABLE void QWebApiHandler::fetchData(const QString& zipCode, const QString& countryCode)
{
	auto jsonResponse = webApiHandler_->fetchData(zipCode.toStdString(), countryCode.toStdString());
	fetchedData_ = QString(jsonResponse.get().serialize().c_str());
}

Q_INVOKABLE QString QWebApiHandler::getLastFetchedData()
{
	return fetchedData_;
}

}