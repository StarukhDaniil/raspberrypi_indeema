cmake_minimum_required(VERSION 3.10)
project(rpi_learning)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(common)

find_package(jsoncpp CONFIG REQUIRED)

file(GLOB SRC "${CMAKE_SOURCE_DIR}/common/src/*.cpp")

add_executable(rpi_learning main.cpp ${SRC})

target_include_directories(rpi_learning PRIVATE "${CMAKE_SOURCE_DIR}/common/include")

target_link_libraries(rpi_learning PRIVATE
                                        common
                                        tsafecontainer
                                        JsonCpp::JsonCpp
                                        "${CMAKE_SOURCE_DIR}/common/lib/libserial.a"
                                        pthread)