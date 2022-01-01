cmake_minimum_required(VERSION 3.21.0)

project(renderer)

set(GCC_FLAGS "-DGLEW_STATIC -Wall -std=c++17")
set(VENDOR_FLAGS "-lglew32s -lglfw3 -lopengl32 -lgdi32")

set(CMAKE_CXX_FLAGS "${GCC_FLAGS}  -L../thirdparty/lib ${SF_LIB}")
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

add_executable(App ${PROJECT_SOURCE_DIR}/renderer/main.cpp)

file(GLOB HEADERS_ ${PROJECT_SOURCE_DIR}/renderer/*.hpp)
file(GLOB CPP_ ${PROJECT_SOURCE_DIR}/renderer/*.hpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_library(applib ${HEADERS_} {CPP_})

target_link_libraries(renderer applib ${SF_LIB} ${ICON_RES})