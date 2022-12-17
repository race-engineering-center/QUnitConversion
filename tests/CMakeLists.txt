cmake_minimum_required(VERSION 3.19)

include_guard(GLOBAL)

project(QUnitConversionTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_AUTOMOC On)
set(CMAKE_AUTORCC On)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

set(SOURCES
        main.cpp
        qaliasdictionarytests.cpp
        qlinearfunctiontests.cpp
        qunitconvertortests.cpp
        )

set(HEADERS
        qaliasdictionarytests.h
        qlinearfunctiontests.h
        qunitconvertortests.h
        )

add_executable(QUnitConversionTests
        ${SOURCES}
        ${HEADERS}
        resources.qrc
        )

target_link_libraries(QUnitConversionTests
        Qt::Core
        Qt::Test
        QUnitConversion
        )
