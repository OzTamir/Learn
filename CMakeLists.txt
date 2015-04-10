cmake_minimum_required(VERSION 3.1)
project(Learn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(Learn ${SOURCE_FILES} hash_table.h hash_table.c main.c)