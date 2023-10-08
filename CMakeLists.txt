cmake_minimum_required(VERSION 3.26)
project(word_search)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(word_search
        include/global.h
        include/input.h
        include/output.h
        include/parser.h
        include/search.h
        include/soup_field.h
        main.cpp)
