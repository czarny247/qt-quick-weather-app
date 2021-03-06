import QtPositioning 5.11
import QtQml 2.14
import Qt.WeatherApiHandler 1.0

PositionSource {
    id: src
    updateInterval: 60000 //miliseconds
    active: true
    preferredPositioningMethods: PositionSource.AllPositioningMethods

    Component.onCompleted: {
        src.start()
        src.update()
        var supPos  = "Unknown"
        if (src.supportedPositioningMethods == PositionSource.NoPositioningMethods) {
            supPos = "NoPositioningMethods"
        } else if (src.supportedPositioningMethods == PositionSource.AllPositioningMethods) {
            supPos = "AllPositioningMethods"
       	} else if (src.supportedPositioningMethods == PositionSource.SatellitePositioningMethods) {
            supPos = "SatellitePositioningMethods"
        } else if (src.supportedPositioningMethods == PositionSource.NonSatellitePositioningMethods) {
            supPos = "NonSatellitePositioningMethods"
        }
       	
        //todo: make logger class
        if(OpenWeatherMapApi.isDebug())
        {
            console.log("Position Source Loaded || Supported: "+supPos+" Valid: "+valid);
        }
        OpenWeatherMapApi.getData(src.position.coordinate)
    }

    onPositionChanged: {
    	OpenWeatherMapApi.getData(src.position.coordinate)
    }
}