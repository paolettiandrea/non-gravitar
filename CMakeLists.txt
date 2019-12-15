cmake_minimum_required(VERSION 3.15)
project(non_gravitar)

set(CMAKE_CXX_STANDARD 17)

add_executable(non_gravitar main.cpp)

#target_compile_options(non_gravitar PUBLIC --coverage)
#target_link_options(non_gravitar PUBLIC --coverage)

add_subdirectory(lib/SGE)
add_subdirectory(src)
add_subdirectory(res)

target_link_libraries(non_gravitar SGE)