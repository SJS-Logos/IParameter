cmake_minimum_required(VERSION 3.28.1)
project(IParameter)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/LogosCmakeScripts/cmake")

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
