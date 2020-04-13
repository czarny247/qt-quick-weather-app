#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QString>

namespace temperature_scale
{

Q_NAMESPACE

inline void registerInQml()
{
    qmlRegisterUncreatableMetaObject(
    	temperature_scale::staticMetaObject, 
        "SharedEnums.TemperatureScale", 1, 0, "TemperatureScale", "Error: only enums");
}

enum class TemperatureScale
{
	Kelvin,
	Celsius,
	Fahrenheit
};

Q_ENUM_NS(TemperatureScale)

inline static QString temperatureUnit(TemperatureScale scale)
{
	switch(scale)
	{

	case TemperatureScale::Kelvin:
		return QString("K");
	case TemperatureScale::Celsius:
		return QString("\u2103");
	case TemperatureScale::Fahrenheit:
		return QString("\u2109");

	}
}

}