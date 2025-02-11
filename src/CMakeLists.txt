include(versioning)
parseVersionFile(fileVersion)
project(IParameter VERSION ${fileVersion})
set(LIB_NAME "${PROJECT_NAME}")
cmake_minimum_required(VERSION 3.28.1)


message("Building " ${PROJECT_NAME} " as static library")
message("Current source dir " "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(${LIB_NAME} STATIC
		util/StringUtil.cpp
)

target_link_libraries(${LIB_NAME} PUBLIC
        Logos::OsInterface
        Logos::OsUtil
)

target_include_directories(${LIB_NAME}
		PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<INSTALL_INTERFACE:include>
)
add_library(Logos::${PROJECT_NAME} ALIAS ${LIB_NAME})

