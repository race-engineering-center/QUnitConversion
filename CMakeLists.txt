cmake_minimum_required(VERSION 3.19)
project(QUnitConversion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(SOURCES
    src/qlinearfunction.cpp
)

set(HEADERS
    src/qaliasdictionary.h
    src/qlinearfunction.h
    src/qunitconversionrule.h
    src/qunitconvertor.h
)

add_library(QUnitConversion STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(QUnitConversion PUBLIC
    src
)

option(QUNITCONV_BUILD_TESTS "Build QUnitConversion unittests" ON)

if(QUNITCONV_BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.18.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    option(QUNITCONV_QT_TESTS "Include Qt string types in typed tests" OFF)

    add_executable(QUnitConversionTests
        src/qaliasdictionary_tests.cpp
        src/qlinearfunction_tests.cpp
        src/qunitconvertor_tests.cpp
    )

    target_link_libraries(QUnitConversionTests
        GTest::gtest_main
        QUnitConversion
    )

    if(QUNITCONV_QT_TESTS)
        find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
        find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
        target_link_libraries(QUnitConversionTests Qt::Core)
        target_compile_definitions(QUnitConversionTests PRIVATE QUNITCONV_QT_TESTS)
    endif()

    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(QUnitConversionTests)
endif()
