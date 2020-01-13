#ifndef NON_GRAVITAR_LASER_HPP
#define NON_GRAVITAR_LASER_HPP

#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/VertArray.hpp>
#include <SGE/utils/animation/Animation.hpp>

#define NG_LASER_RAY_CAST_PERIOD 1/60.0

struct LaserBuildData {
    sge::Vec2<float> starting_pos;
    sge::Vec2<float> ending_pos;
    b2Filter filter;
    Rigidbody_H ingore_rb;
    float duration = 3.0;
    float fade_in_duration = 0.5;
    float width = 0.15;
};

class Laser : public sge::Logic {
public:
    explicit Laser(const LaserBuildData& data);

    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

private:
    VertArray_H vert_array;
    sge::RayCastHandler ray_cast_handler;
    float ray_cast_counter = NG_LASER_RAY_CAST_PERIOD;
    float total_counter = 0;
    float laser_total_duration;
    sge::Animation width_animation;
    float displayed_width;
    sge::Vec2<float> width_lateral_offset;

    void set_width(float new_width);

};


#endif //NON_GRAVITAR_LASER_HPP
