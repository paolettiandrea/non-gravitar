#include <iostream>
#include "Perlin.hpp"

NoiseMap Perlin::fill_noise_map(NoiseMap& out_map, bool random_seed) {
    if (m_frequencies.empty()) {
        std::cout << "No octaves, impossible to generate Perlin noise map" << std::endl;
    }
    PerlinNoise noise_generator;
    if (random_seed) noise_generator.set_seed(time(nullptr));

    for (int x = 0; x < out_map.width; ++x) {
        for (int y = 0; y < out_map.height; ++y) {

            float noise_val = 0.f;
            float offset = 0.f;

            for (int i = 0; i < m_amplitudes.size(); ++i) {
                float sample_x = x/m_scale*m_frequencies[i] + offset;
                float sample_y = y/m_scale*m_frequencies[i];
                float perlin_value = noise_generator.noise(sample_x, sample_y, 0.f);

                noise_val += perlin_value*m_amplitudes[i];
                offset += 1000*i;
            }
            out_map[x][y] = noise_val;
        }
    }
    out_map.normalize(0,1);

    return out_map;
}

void Perlin::simple_setup(unsigned int octaves, float persistence, float lacunarity) {
    m_frequencies.resize(octaves);
    m_amplitudes.resize(octaves);
    m_frequencies[0] = 1.f;
    m_amplitudes[0] = 1.f;
    for (int i = 1; i < octaves; ++i) {
        m_frequencies[i] = m_frequencies[i-1] * lacunarity;
        m_amplitudes[i] = m_amplitudes[i-1] * persistence;
    }
}

void Perlin::add_octave(float frequency, float amplitude) {
    m_frequencies.push_back(frequency);
    m_amplitudes.push_back(amplitude);
}

Perlin::Perlin(float scale) : m_scale(scale) {}
