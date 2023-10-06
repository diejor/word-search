cmake_minimum_required(VERSION 3.21)
project(word-search LANGUAGES CXX)

set(TARGET ${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")

# List your source files explicitly
set(SOURCES
    ${SOURCE_PATH}/main.cpp
    ${SOURCE_PATH}/input.cpp
    ${SOURCE_PATH}/parser.cpp
    ${SOURCE_PATH}/search.cpp
    ${SOURCE_PATH}/output.cpp
)

include_directories( ${INCLUDE_PATH} )
add_executable(${TARGET} ${SOURCES})

target_include_directories(${TARGET} PUBLIC ${INCLUDE_PATH})

install(
    TARGETS ${TARGET}
    RUNTIME DESTINATION bin
)