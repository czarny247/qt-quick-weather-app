import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

GridLayout {
	columns: 2

	property alias zip_code: zip_code.text
	property alias country_code: country_code.text

	GridLayout {
		id: text
		columns: 1
		TextField {
			id: zip_code
			placeholderText: qsTr("Enter zip code")
		}
		TextField {
			id: country_code
			placeholderText: qsTr("Enter country code")
		}
	}
}