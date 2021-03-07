import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

ColumnLayout {

	property alias cityName: cityName
	property alias temperature: temperature

	RowLayout {
		Label {
			text: "City:"
		}
		TextArea {
			id: cityName
			placeholderText: "CityName, CoutryCode"
		}
	}
	RowLayout {
		Label {
			text: "Temperature:"
		}
		TextArea {
			id: temperature
			placeholderText: "Temperature in Celsius"
		}
	}
}