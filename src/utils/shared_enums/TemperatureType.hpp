#pragma once

#include <QObject>
#include <QQmlEngine>

namespace temperature_type
{

Q_NAMESPACE

inline void registerInQml()
{
    qmlRegisterUncreatableMetaObject(
    	temperature_type::staticMetaObject, 
        "SharedEnums.TemperatureType", 1, 0, "TemperatureType", "Error: only enums");
}

enum class TemperatureType
{
	Average,
	Max,
	Min,
	FeelsLike,
	All //handle all
};

Q_ENUM_NS(TemperatureType)

}