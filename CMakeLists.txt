cmake_minimum_required(VERSION 3.23)

project(colmap)

find_package(COLMAP REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${COLMAP_INCLUDE_DIRS})
link_directories(${COLMAP_LINK_DIRS})

add_executable(aaa main.cpp)
target_link_libraries(aaa ${COLMAP_LIBRARIES})