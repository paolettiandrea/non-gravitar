target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE

        Square.cpp
        Square.hpp
        )

add_subdirectory(nodes)