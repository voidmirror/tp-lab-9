cmake_minimum_required(VERSION 3.15)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME task1)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

add_executable(task1 src/task1.cpp)
add_executable(task2 src/task2.cpp)
add_executable(task3 src/task3.cpp)