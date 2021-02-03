#include "backend/WeatherApiConstants.hpp"
#include "backend/WeatherApiHandler.hpp"
#include "qtquick/QWeatherApiHandler.hpp"
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <iostream>
#include <memory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "utils/shared_enums/TemperatureType.hpp"
#include "utils/shared_enums/TemperatureScale.hpp"

using namespace backend;
using namespace concurrency::streams;
using namespace qtquick;
using namespace utility;
using namespace web::http::client;
using namespace web::http;
using namespace web::json;
using namespace web;

int main(int argc, char *argv[])
{
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	std::shared_ptr<WeatherApiHandler> openWeatherMapApi = std::make_shared<WeatherApiHandler>(
		std::string(openWeatherMapApiUrl),
		std::string(openWeatherMapApiUriPrefix));

	QCoreApplication::addLibraryPath("./");

	QQmlApplicationEngine appEngine;

	//move to class - static method
	qmlRegisterSingletonType<QWeatherApiHandler>("Qt.WeatherApiHandler", 1, 0, "OpenWeatherMapApi",
		[&openWeatherMapApi](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject *
		{
			Q_UNUSED(engine)
			Q_UNUSED(scriptEngine)

			QWeatherApiHandler *handler = new QWeatherApiHandler(openWeatherMapApi);
			return handler;
		});

	qmlRegisterSingletonType(QUrl("qrc:/ScaleProperties.qml"), "Qt.ScaleProperties", 1, 0, "ScaleProperties");

	temperature_type::registerInQml();
	temperature_scale::registerInQml();

	appEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}