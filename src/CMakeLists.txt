cmake_minimum_required(VERSION 3.2)
project(dust)

add_subdirectory(async)

add_library( dust
    Human.cpp
    Human.h
)

link_libraries(dust async)