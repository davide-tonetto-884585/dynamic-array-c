cmake_minimum_required(VERSION 3.17)
project(dynamic_array C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -finline-functions")

add_executable(dynamic_array main.c dynarr.h dynarr.c)

target_link_libraries(dynamic_array m)