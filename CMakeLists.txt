cmake_minimum_required(VERSION 2.8)

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME labThreads) 
project(${PROJECT_NAME})

set(SRC_FILES1 ${PROJECT_SOURCE_DIR}/src/main.cpp)
set(SRC_FILES2 ${PROJECT_SOURCE_DIR}/include/task1.h)
set(SRC_FILES2 ${PROJECT_SOURCE_DIR}/include/task2.h)
set(SRC_FILES2 ${PROJECT_SOURCE_DIR}/include/task3.h)

set(CMAKE_CXX_STANDARD 11)

add_executable(textGenerator ${PROJECT_SOURCE_DIR}/src/main.cpp) 