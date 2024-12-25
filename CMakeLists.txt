cmake_minimum_required(VERSION 3.10)
project(AtsinComestrike)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(thirdparty/fmt)

add_executable(AtsinComestrike src/main.cpp)

target_link_libraries(AtsinComestrike ${SDL2_LIBRARIES} fmt::fmt)

