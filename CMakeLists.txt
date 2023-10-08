cmake_minimum_required(VERSION 3.26)
project(word_search)

set(CMAKE_CXX_STANDARD 17)

set(TARGET word_search)

include_directories(include)

add_executable(${TARGET}
        include/global.h
        include/input.h
        include/output.h
        include/parser.h
        include/search.h
        include/soup_field.h
        main.cpp)
