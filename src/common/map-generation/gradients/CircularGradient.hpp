#ifndef PERLIN_TESTS_CIRCULARGRADIENT_HPP
#define PERLIN_TESTS_CIRCULARGRADIENT_HPP


#include "SGE/utils/interpolation/Interpolator.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

#include "Gradient.hpp"

class CircularGradient : public Gradient {
public:
    CircularGradient(float outer_radius, float inner_radius, float pos_x, float pos_y, float central_val, float outer_val, Interpolator* algorithm);

    float get_val(float x, float y) const override;

private:
    float m_outer_radius;
    float m_inner_radius;
    float m_pos_x, m_posy;

};





#endif //PERLIN_TESTS_CIRCULARGRADIENT_HPP
