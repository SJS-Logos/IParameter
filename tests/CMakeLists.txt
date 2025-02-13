cmake_minimum_required(VERSION 3.18)

set(TEMP_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/temp/includes/")

add_executable(unit_tests
    ParameterTest.cpp
)

message(STATUS "gtest_SOURCE_DIR is ${gtest_SOURCE_DIR}")

target_include_directories(unit_tests PRIVATE
        ${gtest_SOURCE_DIR}/include
)

target_link_libraries(unit_tests
        PRIVATE

        Logos::IParameterLib
        GTest::gtest_main
        )
target_include_directories(unit_tests
        PRIVATE
        ${TEMP_INCLUDE_DIR}
        )
if(NOT ${CMAKE_CROSSCOMPILING})
    include(GoogleTest)
    gtest_discover_tests(unit_tests)
else()
    message(STATUS "Skipping gtest discover due to usage of toolchain ${CMAKE_TOOLCHAIN_FILE}")
endif()