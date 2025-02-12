cmake_minimum_required(VERSION 3.18)


set(TEMP_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/temp/includes/")

add_executable(${PROJECT_NAME}
        ParameterTest.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE

        Logos::IParameter
        gmock_main
        gtest
        gmock
        )
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${TEMP_INCLUDE_DIR}
        )
if(NOT ${CMAKE_CROSSCOMPILING})
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME})
else()
    message(STATUS "Skipping gtest discover due to usage of toolchain ${CMAKE_TOOLCHAIN_FILE}")
endif()