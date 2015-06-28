cmake_minimum_required(VERSION 3.2)
project(dust)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(dust ${SOURCE_FILES} src/Human.cpp src/Human.h)