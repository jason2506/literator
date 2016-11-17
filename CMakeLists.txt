cmake_minimum_required(VERSION 3.1)

project(literator
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
install(DIRECTORY ${${PROJECT_NAME}_INCLUDE_DIR}/
    DESTINATION include
    PATTERN *.hpp
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${${PROJECT_NAME}_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)

include(cmake/literatorPackage.cmake)
