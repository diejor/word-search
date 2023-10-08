cmake_minimum_required(VERSION 3.21)
project(word-search LANGUAGES CXX)

set(TARGET ${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")

file (GLOB_RECURSE SOURCES "${SOURCE_PATH}/*.cpp")

include_directories( "${INCLUDE_PATH}" "${SOURCE_PATH}")

add_executable(${TARGET} ${SOURCES}
        src/soup_field.cpp
        include/soup_field.h)

target_include_directories(${TARGET} PUBLIC ${INCLUDE_PATH})