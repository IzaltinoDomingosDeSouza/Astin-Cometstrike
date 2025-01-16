cmake_minimum_required(VERSION 3.10)
project(AtsinComestrike)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/SDL_image)
add_subdirectory(thirdparty/fmt)

include_directories(${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS} ${fmt_INCLUDE_DIRS})

add_executable(AtsinComestrike src/main.cpp)

target_link_libraries(AtsinComestrike SDL3::SDL3 SDL3_image::SDL3_image fmt::fmt)

