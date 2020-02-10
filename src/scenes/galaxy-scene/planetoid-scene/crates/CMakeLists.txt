target_sources(non_gravitar PRIVATE
        Crate.cpp
        Crate.hpp
        )

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(data)