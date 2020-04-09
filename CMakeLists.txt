cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(qt-quick-weather-app)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# if(CMAKE_VERSION VERSION_LESS "3.7.0")
#     set(CMAKE_INCLUDE_CURRENT_DIR ON)
# endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # set(MACOSX TRUE)
    set(Qt5QuickCompiler_DIR "/usr/local/opt/qt5/lib/cmake/Qt5QuickCompiler")
    set(Qt5_DIR "/usr/local/opt/qt5/lib/cmake/Qt5")
    # set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl@1.1")
    #"OPENSSL_ROOT_DIR", "/usr/local/opt/openssl/"
endif()

find_package(cpprestsdk REQUIRED)
find_package(Qt5 REQUIRED Qml Quick Gui Core)
find_package(Qt5QuickCompiler)
qt5_add_resources(qml_QRC src/qml.qrc)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCE 
	${SOURCE}
	src/main.cpp
	src/backend/WebApiHandler.hpp
	src/backend/WebApiHandler.cpp
	src/qtquick/QWebApiHandler.hpp
	src/qtquick/QWebApiHandler.cpp
)

add_executable(qt-quick-weather-app ${SOURCE} ${qml_QRC})

target_link_libraries(qt-quick-weather-app PRIVATE Qt5::Qml Qt5::Quick cpprestsdk::cpprest)