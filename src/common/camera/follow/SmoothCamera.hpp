#ifndef NON_GRAVITAR_SMOOTHCAMERA_HPP
#define NON_GRAVITAR_SMOOTHCAMERA_HPP


#include <player/PlayerPersistentData.hpp>
#include <SGE/logic/Logic.hpp>

#define ZOOM_SPEED 10
#define SHARPNESS  10


class SmoothCamera : public sge::Logic {
public:

    void set_follow(GameObject_H target_go);


private:
    GameObject_H follow_go;
    sge::Vec2<float> target_pos;
public:
    void on_update() override;

    std::string get_logic_id() override;

    void on_fixed_update() override;

private:

    float lerp (float current, float target, float sharpness);
    sge::Vec2<float> lerp (sge::Vec2<float> current, sge::Vec2<float> target, float sharpness);
};


#endif //NON_GRAVITAR_SMOOTHCAMERA_HPP
