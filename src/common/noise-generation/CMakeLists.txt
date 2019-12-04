target_include_directories(non_gravitar PRIVATE .)

target_sources(non_gravitar PRIVATE

        NoiseMap.cpp
        NoiseMap.hpp

        PerlinNoise.cpp
        PerlinNoise.hpp

        Perlin.hpp
        Perlin.cpp
        )