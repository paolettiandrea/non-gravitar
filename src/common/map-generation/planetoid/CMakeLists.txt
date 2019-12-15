target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE
        Planetoid.cpp
        Planetoid.hpp

        PlanetoidPersistentData.cpp
        PlanetoidPersistentData.hpp
        )