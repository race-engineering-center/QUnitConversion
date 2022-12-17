cmake_minimum_required(VERSION 3.19)
project(QUnitConversion)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(QUnitConversion)

option(QUNITCONV_BUILD_TESTS "Build QUnitConversion unttests" On)

if (QUNITCONV_BUILD_TESTS)
    add_subdirectory(tests)
endif()
