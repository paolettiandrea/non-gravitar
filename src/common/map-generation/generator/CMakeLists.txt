target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE

        MapGenerator.hpp
        MapGenerator.cpp

        PlanetoidPopulator.cpp
        PlanetoidPopulator.hpp

        MapGenInfo.cpp
        MapGenInfo.hpp

        Region.hpp
        Region.cpp

        RegionDistanceData.hpp
        RegionDistanceData.cpp

        EnemyPersistentData.hpp
        BasicEnemyBuildData.hpp
        )

add_subdirectory(marching-squares)