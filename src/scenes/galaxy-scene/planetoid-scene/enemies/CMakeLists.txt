target_sources(non_gravitar PRIVATE
        Enemy.cpp
        Enemy.hpp
        )

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(data)
add_subdirectory(parts)