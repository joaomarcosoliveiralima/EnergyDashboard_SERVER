cmake_minimum_required(VERSION 3.14)

project(EnergyDashboardS_SERVER VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Xml Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Xml Sql REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        http/httprequest.cpp
        http/httpstatuscodes.cpp
        http/httpwebengine.cpp
        tcp/tcpmultithreadedserver.cpp
        tcp/tcpserverthread.cpp
        misc/log.cpp
        misc/logger.cpp
        http/httpresource.cpp
        http/httpiodeviceresource.cpp
        util/utilassetsresource.cpp
        http/httpresponse.cpp
        http/httpheaders.cpp
        util/utildataurlcodec.cpp
        util/utilformurlcodec.cpp

        http/httprequest.h
        http/httpstatuscodes.h
        http/httpwebengine.h
        tcp/tcpserverthread.h
        tcp/tcpmultithreadedserver.h
        tcp/tcpresponder.h
        misc/threadsafety.h
        misc/logger.h
        misc/log.h
        http/httpresource.h
        http/httpiodeviceresource.h
        util/utilassetsresource.h
        http/httpresponse.h
        http/httpheaders.h
        util/utildataurlcodec.h
        util/utilformurlcodec.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EnergyDashboardS_SERVER
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(EnergyDashboardS_SERVER SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(EnergyDashboardS_SERVER
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(EnergyDashboardS_SERVER
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(EnergyDashboardS_SERVER
  PRIVATE   Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Xml
            Qt${QT_VERSION_MAJOR}::Quick
            Qt${QT_VERSION_MAJOR}::Network
            Qt${QT_VERSION_MAJOR}::Sql
            Qt${QT_VERSION_MAJOR}::Gui)

set_target_properties(EnergyDashboardS_SERVER PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(EnergyDashboardS_SERVER)
    qt_finalize_executable(EnergyDashboardS_SERVER)
endif()
