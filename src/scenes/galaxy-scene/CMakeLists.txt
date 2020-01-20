target_sources(non_gravitar PRIVATE
        GalaxyScene_EntryLogic.cpp
        GalaxyScene_EntryLogic.hpp

        Galaxy_ConstructionData.hpp
        )

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(game-scene)
add_subdirectory(death-scene)
add_subdirectory(scaled-planetoid)
add_subdirectory(scene-transition)
