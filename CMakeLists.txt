cmake_minimum_required(VERSION 3.28.1)
project(IParameter)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/LogosCmakeScripts/cmake")

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

set(EXTERNALS
        OsInterface
        OsUtil
        LogosText
        iDebugDummy
)

foreach(external ${EXTERNALS})
    add_subdirectory("${external}/src")
endforeach()

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)
