cmake_minimum_required(VERSION 3.2)
project(dust)

add_library( thread
    PThread.cpp
    PThread.h
)
