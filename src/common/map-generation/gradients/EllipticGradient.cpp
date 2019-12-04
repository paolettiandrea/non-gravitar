//
// Created by andrea on 6/7/19.
//

#include "EllipticGradient.hpp"

float EllipticGradient::get_val(float x, float y) const {
    float t;
    if ((x > m_bound_max_x || x < m_bound_min_x) || (y > m_bound_max_y || y < m_bound_min_y) ) {
        t = 1.f;
    } else {
        float sum_dist = distance(x, y, m_x2, m_y2) + distance(m_x1, m_y1, x, y);
        t = (sum_dist - m_dist) / m_factor;
        if (t > 1) t = 1.f;
    }

    return m_algorithm->interpolate(t,m_val_a,m_val_b);
}

EllipticGradient::EllipticGradient(float valA, float valB, Interpolator* algorithm, float mX1, float mY1, float mX2,
                               float mY2, float max_dist) : Gradient(valA, valB, algorithm), m_x1(mX1), m_x2(mX2),
                                                          m_y1(mY1), m_y2(mY2), m_factor(max_dist) {
    m_dist = distance(m_x1,m_y1,m_x2,m_y2);

    float margin = m_dist;
    m_bound_max_x = std::fmax(mX1,mX2) + margin;
    m_bound_max_y = std::fmax(mY1,mY2) + margin;
    m_bound_min_x = std::fmin(mX1,mX2) - margin;
    m_bound_min_y = std::fmin(mY1,mY2) - margin;
}
