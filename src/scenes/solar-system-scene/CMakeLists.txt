target_sources(non_gravitar PRIVATE
        SolarSystemScene_EntryLogic.cpp
        SolarSystemScene_EntryLogic.hpp

        SolarSystem_ConstructionData.hpp

        PlanetoidManager.cpp
        PlanetoidManager.hpp
        )

target_include_directories(non_gravitar PRIVATE .)

add_subdirectory(planetoid-scene)
add_subdirectory(death-scene)
add_subdirectory(scaled-planetoid)
add_subdirectory(scene-transition)
