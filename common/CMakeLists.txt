file(GLOB SRC
    src/jsonparser.cpp
    src/logger.cpp
    src/tsafecontainer.cpp
    src/serial_listener.cpp)

find_package(jsoncpp REQUIRED)

add_library(common STATIC ${SRC})

target_link_libraries(common PRIVATE 
    JsonCpp::JsonCpp
    serial)

target_include_directories(common PUBLIC
    include)