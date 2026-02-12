cmake_minimum_required(VERSION 3.10)
project(rpi_learning)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(common)

add_executable(rpi_learning main.cpp)

target_link_libraries(rpi_learning PRIVATE common)