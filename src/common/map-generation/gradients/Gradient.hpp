//
// Created by andrea on 6/7/19.
//

#ifndef PERLIN_TESTS_GRADIENT_HPP
#define PERLIN_TESTS_GRADIENT_HPP

#include "SGE/utils/interpolation/Interpolator.hpp"
/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class Gradient {
public:
    Gradient(float val_a, float val_b, Interpolator* algorithm) : m_val_a(val_a), m_val_b(val_b), m_algorithm(algorithm) {}

    virtual ~Gradient() {
        delete (m_algorithm);
    }

    virtual float get_val(float x, float y) const = 0;

    void set_extremes(float a, float b) {
        m_val_a = a;
        m_val_b = b;
    }

    float get_extreme_a() const { return m_val_a; }
    float get_extreme_b() const { return m_val_b; }

protected:
    float m_val_a, m_val_b;
    Interpolator* m_algorithm;
};

#endif //PERLIN_TESTS_GRADIENT_HPP
