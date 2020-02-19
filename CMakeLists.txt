cmake_minimum_required(VERSION 3.13)
project(non_gravitar)

set(CMAKE_CXX_STANDARD 11)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(non_gravitar main.cpp)

add_subdirectory(lib/SGE)
add_subdirectory(src)
add_subdirectory(res)

target_link_libraries(non_gravitar SGE)