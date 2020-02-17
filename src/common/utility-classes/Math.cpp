#include "Math.hpp"

float Math::lerp(float current, float target, float sharpness) {
    return current + sharpness * (target - current);
}

sge::Vec2<float> Math::lerp(sge::Vec2<float> current, sge::Vec2<float> target, float sharpness) {
    float x = lerp(current.x, target.x, sharpness);
    float y = lerp(current.y, target.y, sharpness);
    return sge::Vec2<float>(x, y);
}
