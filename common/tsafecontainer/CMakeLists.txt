file(GLOB SRC ./src/*.cpp)

add_library(tsafecontainer STATIC SRC)

target_include_directories(tsafecontainer PUBLIC include)