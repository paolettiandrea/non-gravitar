#include "CircularGradient.hpp"
#include <cmath>
#include <iostream>

CircularGradient::CircularGradient(float outer_radius, float inner_radius, float pos_x, float pos_y, float central_val, float outer_val, Interpolator* algorithm)
        : Gradient(central_val,outer_val,algorithm), m_outer_radius(outer_radius), m_inner_radius(inner_radius), m_pos_x(pos_x), m_posy(pos_y) {}

float CircularGradient::get_val(float x, float y) const {
    if (m_inner_radius>=0 && m_outer_radius>m_inner_radius) {
        float distance = sqrtf(powf(x-m_pos_x,2) + powf(y-m_posy,2));
        if (distance<m_outer_radius) {
            if (distance > m_inner_radius) {
                float t = (distance-m_inner_radius)/(m_outer_radius-m_inner_radius);
                return m_algorithm->interpolate(t,m_val_a, m_val_b);
            } else
                return m_val_a;
        } else
            return m_val_b;
    } else {
        std::cout << " Wrong radiuses" << std::endl;
        exit(1);
    }
}





