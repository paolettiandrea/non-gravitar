#ifndef PERLIN_TESTS_PERLIN_HPP
#define PERLIN_TESTS_PERLIN_HPP

#include "PerlinNoise.hpp"
#include "NoiseMap.hpp"
#include <limits>
#include "time.h"
#include <vector>

class Perlin {
public:
    Perlin (float scale);
    NoiseMap fill_noise_map(NoiseMap& out_map, bool random_seed = false);

    void simple_setup(unsigned int octaves, float persistence, float lacunarity);

    void add_octave(float frequency, float amplitude);


private:
    float m_scale;
    std::vector<float> m_frequencies;
    std::vector<float> m_amplitudes;
};


#endif //PERLIN_TESTS_PERLIN_HPP
