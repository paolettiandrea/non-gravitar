target_sources(non_gravitar PRIVATE
        PlanetoidScene_EntryLogic.hpp
        PlanetoidScene_EntryLogic.cpp
        )

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(enemies)
add_subdirectory(breakable)
add_subdirectory(scene-transition)
add_subdirectory(crates)
