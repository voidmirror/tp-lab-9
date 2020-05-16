cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
project(clab9)

set(CMAKE_CXX_STANDARD 14)

add_executable(clab9 src/main.cpp include/task1.h include/task2.h include/task3.h)