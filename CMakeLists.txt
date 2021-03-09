cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(qt-quick-weather-app)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#todo build default for host or non-default for chosen system
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(Qt5QuickCompiler_DIR "/usr/local/opt/qt5/lib/cmake/Qt5QuickCompiler")
    set(Qt5_DIR "/usr/local/opt/qt5/lib/cmake/Qt5")
endif()

if(API_KEY)
	configure_file(src/backend/ApiKey.hpp.in src/backend/ApiKey.hpp)
else()
	message(FATAL_ERROR "Missing API_KEY! Check details in README") #todo add instructions to readme
	#todo get api key from jsonfile - prepare json template
endif()

find_package(cpprestsdk REQUIRED)
find_package(Qt5 REQUIRED 
	Qml
	Quick
	Gui
	Core
	Positioning
	Network)
find_package(Qt5QuickCompiler)
qt5_add_resources(qml_QRC src/qml.qrc)
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src
	${PROJECT_BINARY_DIR}/src)

set(SOURCE
	${SOURCE}
	src/main.cpp
	src/utils/shared_enums/TemperatureScale.hpp
	src/utils/shared_enums/TemperatureType.hpp
	src/backend/WeatherApiHandler.hpp
	src/backend/WeatherApiHandler.cpp
	src/backend/WeatherApiResponseData.hpp
	src/backend/WeatherApiResponseData.cpp
	src/qtquick/QWeatherApiHandler.hpp
	src/qtquick/QWeatherApiHandler.cpp
	src/3party/HttpStatusCodes_C++11.h
	${PROJECT_BINARY_DIR}/src/backend/ApiKey.hpp
)

set(PRIVATE_LINK_LIBRARIES
	Qt5::Qml
	Qt5::Quick
	Qt5::Positioning
	Qt5::Network)

add_executable(qt-quick-weather-app ${SOURCE} ${qml_QRC})
target_link_libraries(qt-quick-weather-app PRIVATE ${PRIVATE_LINK_LIBRARIES})