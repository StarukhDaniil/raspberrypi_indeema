cmake_minimum_required(VERSION 3.10)
project(rpi_learning)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(common)

find_package(jsoncpp CONFIG REQUIRED)

add_executable(rpi_learning main.cpp)

set(SERIAL_ROOT "${CMAKE_SOURCE_DIR}/third_party/serial")

target_include_directories(rpi_learning PRIVATE "${SERIAL_ROOT}/include")

target_link_libraries(rpi_learning PRIVATE
                                        common
                                        JsonCpp::JsonCpp
                                        "${SERIAL_ROOT}/lib/libserial.a"
                                        pthread)