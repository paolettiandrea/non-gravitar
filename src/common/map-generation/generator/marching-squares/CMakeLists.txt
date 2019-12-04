target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE

        MarchingMap.cpp
        MarchingMap.hpp
        )

add_subdirectory(squares)