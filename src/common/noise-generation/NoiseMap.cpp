#include "NoiseMap.hpp"
#include <cmath>
#include <limits>
#include <iostream>
#include "SFML/Graphics.hpp"


NoiseMap::NoiseMap(unsigned int _width, unsigned int _height, float initial_val)
        : NoiseMap(_width, _height) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            m_noise_map[x][y] = initial_val;
        }
    }
}

NoiseMap::NoiseMap(unsigned int _width, unsigned int _height)
    : width(_width), height(_height) {
    m_noise_map = new float*[width];
    for (int i = 0; i < width; ++i) {
        m_noise_map[i] = new float[height];
    }
}

NoiseMap::~NoiseMap() {
    for (int i = 0; i < width; ++i) {
        delete[](m_noise_map[i]);
    }
    delete [](m_noise_map);


}

float* NoiseMap::operator[](const int index) {
    return m_noise_map[index];
}

float* NoiseMap::operator[](const int index) const {
    return m_noise_map[index];
}

std::ostream& operator<<(std::ostream& os, const NoiseMap& map) {
    os << "width: " << map.width << " height: " << map.height << " m_noise_map:\n" ;
    for (int i = 0; i < map.width; ++i) {
        for (int j = 0; j < map.height; ++j) {
            os << map[i][j] << "\t";
        }
        os << "\n";
    }
    return os;
}

void NoiseMap::operator*=(const NoiseMap& other) {
    if (other.height==this->height && other.width==this->width) {
        for (int x = 0; x < this->width; ++x) {
            for (int y = 0; y < this->height; ++y) {
                m_noise_map[x][y] *= other[x][y];
            }
        }
    }
}

void NoiseMap::normalize(float min, float max) {

    if (max <= min) {
        std::cout << "ERROR: in NoiseMap normalization the min and the max are switched!" << std::endl;
        exit(1);
    }

    float min_val = std::numeric_limits<float>::max();
    float max_val = std::numeric_limits<float>::min();
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float val = m_noise_map[x][y];
            if (val > max_val) max_val = val;
            if (val < min_val) min_val = val;
        }
    }
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float val = m_noise_map[x][y];
            float t = (val - min_val) / (max_val - min_val);
            m_noise_map[x][y] = min + t*(max-min);
        }
    }
}

void NoiseMap::apply_gradient_as_mask(const Gradient& gradient) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            m_noise_map[x][y] = m_noise_map[x][y] * gradient.get_val(x,y);
        }
    }
}

void NoiseMap::apply_gradient_as_min(const Gradient& gradient) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float gradient_val = gradient.get_val(x,y);
            float noise_map_val = m_noise_map[x][y];
            if (gradient_val>noise_map_val) m_noise_map[x][y] = gradient_val;
        }
    }
}

void NoiseMap::weighted_average(const NoiseMap& other_map, const Gradient& gradient) {
    if (width == other_map.width && height == other_map.height) {
        if (gradient.get_extreme_a() >= 0 && gradient.get_extreme_a() <= 1.f &&
            gradient.get_extreme_b() >= 0 && gradient.get_extreme_b() <= 1.f) {
            for (int x = 0; x < width; ++x) {
                for (int y = 0; y < height; ++y) {
                    float other_val = other_map[x][y];
                    float this_val = m_noise_map[x][y];
                    float other_weight = gradient.get_val(x,y);
                    m_noise_map[x][y] = other_val*other_weight + this_val*(1-other_weight);
                }
            }
        } else {
            std::cout << "In order to average two noise maps the gradient extremes needs to be between 0 and 1" << std::endl;
            exit(1);
        }
    } else {
        std::cout << "The two maps have different dimensions" << std::endl;
        exit(1);
    }
}

void NoiseMap::apply_threshold(float threshold_val, float above_val, float below_val) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (m_noise_map[x][y]>threshold_val) m_noise_map[x][y] = above_val;
            else m_noise_map[x][y] = below_val;
        }
    }
}

void NoiseMap::save_as_image(const std::string& name, float expected_min, float expected_max) {
    sf::Image image;
    image.create(width, height);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float t = (m_noise_map[x][y]-expected_min)/(expected_max - expected_min);
            if (t>1.f) {
                std::cout << "Got an out of scale value while displaying NoiseMap: [" << m_noise_map[x][y] << "] that resulted in a t value of [" << t
                          << "] while the expected max is : [" << expected_max << "]" << std::endl;
            }
            int lum = (int)floorf(t*255);
            image.setPixel(x,y,sf::Color(lum,lum,lum));
        }
    }
    image.saveToFile(name);
}

NoiseMap::NoiseMap(const NoiseMap& that) : NoiseMap(that.width, that.height, 0){
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            m_noise_map[x][y] = that.m_noise_map[x][y];
        }
    }
}

void NoiseMap::weighted_average(float val, const Gradient& gradient) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float this_val = m_noise_map[x][y];
            float other_weight = gradient.get_val(x,y);
            m_noise_map[x][y] = val*other_weight + this_val*(1-other_weight);
        }
    }
}

void NoiseMap::apply_noisemap_as_mask(const NoiseMap& other_map) {
    if (width == other_map.width && height == other_map.height) {
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                m_noise_map[x][y] = m_noise_map[x][y] * other_map[x][y];
            }
        }
    } else {
        std::cout << "ERROR during apply_noisemap_as_mask, the two noisemaps need to have the same dimensions";
    }

}









