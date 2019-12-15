target_sources(non_gravitar PRIVATE
        MiniaturePlanetoid.cpp
        MiniaturePlanetoid.hpp

        MiniaturePlanetPortal.cpp
        MiniaturePlanetPortal.hpp
        )

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(minimap)