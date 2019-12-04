//
// Created by andrea on 6/7/19.
//

#ifndef PERLIN_TESTS_ELLIPTICGRADIENT_HPP
#define PERLIN_TESTS_ELLIPTICGRADIENT_HPP
#include<math.h>

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
#include "Gradient.hpp"

class EllipticGradient : public Gradient {
public:

    float get_val(float x, float y) const override;



private:
    float m_x1, m_x2, m_y1, m_y2, m_factor, m_dist;
    float m_bound_max_x, m_bound_max_y, m_bound_min_x, m_bound_min_y;
public:
    EllipticGradient(float valA, float valB, Interpolator* algorithm, float mX1, float mY1, float mX2, float mY2,
                   float max_dist);

private:

    float distance(float x1, float y1,float x2, float y2) const {
        return sqrtf(powf(x1-x2,2) + powf(y1-y2,2));
    }
};


#endif //PERLIN_TESTS_ELLIPTICGRADIENT_HPP
