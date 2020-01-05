#ifndef PERLIN_TESTS_NOISEMAP_HPP
#define PERLIN_TESTS_NOISEMAP_HPP


#include "CircularGradient.hpp"
#include <iostream>
#include <SGE/Vec2.hpp>

class NoiseMap {
public:
    const unsigned int width;
    const unsigned int height;

    NoiseMap(unsigned int _width, unsigned int _height);
    NoiseMap(unsigned int _width, unsigned int _height, float initial_val);
    NoiseMap(const NoiseMap& that);
    virtual ~NoiseMap();

    float* operator[] (const int index);

    float* operator[] (const int index) const;

    bool operator==(const NoiseMap& that) {
        if (this->width == that.width && this->height == that.height) {
            for (int x = 0; x < width; ++x) {
                for (int y = 0; y < height; ++y) {
                    if (m_noise_map[x][y]!=that[x][y]) return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }


    NoiseMap& operator=(const NoiseMap &that ) {
        if (width==that.width && height==that.height) {
            for (int x = 0; x < width; ++x) {
                for (int y = 0; y < height; ++y) {
                    m_noise_map[x][y] = that.m_noise_map[x][y];
                }
            }
            return *this;
        } else {
            std::cout << "ERROR: assignment operator cannot be used between NoiseMaps with different dimensions" << std::endl;
            exit(1);
        }
    }

    void operator*= (const NoiseMap& other);

    friend std::ostream& operator<<(std::ostream& os, const NoiseMap& map);

    void normalize(float min, float max);

    void apply_gradient_as_mask(const Gradient& gradient);
    void apply_gradient_as_min(const Gradient& gradient);
    void apply_noisemap_as_mask(const NoiseMap& other_map);

    void weighted_average(const NoiseMap& other_map, const Gradient& gradient);
    void weighted_average(float val, const Gradient& gradient);
    void apply_threshold(float threshold_val, float above_val, float below_val);
    void save_as_image(const std::string& name, float expected_min, float expected_max);

    /*!
     * @param starting_point The point in which to start flooding the map
     * @param target_val The noise value considered floodable, any other value is considered as a wall
     */
    static void flood_fill(NoiseMap& input_map, NoiseMap& out_map, sge::Vec2<int> starting_point, float target_val);

protected:
    float** m_noise_map;
};


#endif //PERLIN_TESTS_NOISEMAP_HPP
