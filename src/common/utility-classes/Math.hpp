#ifndef NON_GRAVITAR_MATH_HPP
#define NON_GRAVITAR_MATH_HPP

#include <SGE/Vec2.hpp>

class Math {
public:
    static float lerp (float current, float target, float sharpness);

    static sge::Vec2<float> lerp(sge::Vec2<float> current, sge::Vec2<float> target, float sharpness);
    };


#endif //NON_GRAVITAR_MATH_HPP
