cmake_minimum_required(VERSION 3.19)

include_guard(GLOBAL)

project(QUnitConversion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_AUTOMOC On)

set(SOURCES
    qlinearfunction.cpp
    qunitconversionfamily.cpp
    qunitconversionrule.cpp

)

set(HEADERS
    qaliasdictionary.h
    qlinearfunction.h
    qunitconversionfamily.h
    qunitconversionrule.h
    qunitconvertor.h
)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_library(QUnitConversion STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(QUnitConversion PUBLIC
    .
)

target_link_libraries(QUnitConversion PUBLIC
    Qt::Core
)
