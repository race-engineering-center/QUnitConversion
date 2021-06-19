cmake_minimum_required(VERSION 3.19)

include_guard(GLOBAL)

project(QUnitConversionTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_AUTOMOC On)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

get_filename_component(QT_TOOLCHAIN ${CMAKE_PREFIX_PATH} NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../build_${QT_VERSION}_${QT_TOOLCHAIN}_${CMAKE_BUILD_TYPE})

set(SOURCES
    main.cpp
    tests/qaliasdictionarytests.cpp
    tests/qlinearfunctiontests.cpp
    tests/qunitconvertortests.cpp
)

set(HEADERS
    tests/qaliasdictionarytests.h
    tests/qlinearfunctiontests.h
    tests/qunitconvertortests.h
)

add_executable(QUnitConversionTests
    ${SOURCES}
    ${HEADERS}
)

add_subdirectory(QUnitConversion)

target_link_libraries(QUnitConversionTests
    Qt::Core
    Qt::Test
    QUnitConversion
)
