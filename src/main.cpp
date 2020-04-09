#include "backend/WebApiConstants.hpp"
#include "backend/WebApiHandler.hpp"
#include "qtquick/QWebApiHandler.hpp"
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <iostream>
#include <memory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

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
    QGuiApplication app(argc, argv);

    std::shared_ptr<WebApiHandler> openWeatherMapApi = std::make_shared<WebApiHandler>(
        std::string(openWeatherMapApiUrl), 
        std::string(openWeatherMapApiUriPrefix));

    QCoreApplication::addLibraryPath("./");

    QQmlApplicationEngine appEngine;

    qmlRegisterSingletonType<QWebApiHandler>("Qt.WebApiHandler", 1, 0, "OpenWeatherMapApi", 
    	[&openWeatherMapApi](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * 
    	{
    		Q_UNUSED(engine)
    		Q_UNUSED(scriptEngine)

    		QWebApiHandler *handler = new QWebApiHandler(openWeatherMapApi);
    		return handler;
		});

    appEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}