cmake_minimum_required(VERSION 2.8)

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME lab9) 
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall")

# If you want your own include/ directory, set this, and then you can do
# include_directories(${COMMON_INCLUDES}) in other CMakeLists.txt files.
# set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Define project sources and includes
#----------------------------------------------------------------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)


# set(SRC_FILES1 ${PROJECT_SOURCE_DIR}/src/task1.cpp)
# set(SRC_FILES2 ${PROJECT_SOURCE_DIR}/src/task2.cpp)
# set(SRC_FILES3 ${PROJECT_SOURCE_DIR}/src/task3.cpp)


set(CMAKE_CXX_STANDARD 17)

# add_library(task1_lib ${SRC_FILES1})
# add_library(task2_lib ${SRC_FILES2})
# add_library(task3_lib ${SRC_FILES3})


add_executable(task1 ${PROJECT_SOURCE_DIR}/src/main.cpp)

# target_link_libraries(task1 task1_lib)
# target_link_libraries(task2 task2_lib)
# target_link_libraries(task3 task3_lib)
