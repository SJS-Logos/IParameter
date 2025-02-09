cmake_minimum_required(VERSION 3.18.1)
project(IParameterTests)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEMP_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/temp/includes/")

add_executable(${PROJECT_NAME}
        ParameterTest.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE

        Logos::iDebugDummy
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