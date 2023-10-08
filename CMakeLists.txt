cmake_minimum_required(VERSION 3.15)
project(word-search)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(TARGET word-search)

include_directories(include)

add_executable(${TARGET} main.cpp)

