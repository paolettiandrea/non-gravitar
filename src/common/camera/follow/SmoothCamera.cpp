#include "SmoothCamera.hpp"
#include "CONTROLS.hpp"


float SmoothCamera::lerp(float current, float target, float sharpness) {
    return current + sharpness * (target - current);
}

void SmoothCamera::set_follow(GameObject_H target_go) {
    follow_go = target_go;
}

void SmoothCamera::on_fixed_update() {
    if (follow_go.is_valid()) {
        target_pos = follow_go->transform()->get_world_position();
    }
    auto current_pos = scene()->get_camera()->get_center();
    float blend = SHARPNESS * env()->fixed_delta_time();
    scene()->get_camera()->set_center(lerp(current_pos, target_pos, blend));


    update_target_zoom();

    float current_zoom = scene()->get_camera()->get_zoom();
    float blend2 = ZOOM_SHARPNESS * env()->fixed_delta_time();
    float new_zoom = lerp(current_zoom, target_zoom, blend2);
    if (current_zoom!=new_zoom) scene()->get_camera()->set_zoom(new_zoom);

}

void SmoothCamera::on_update() {




}

std::string SmoothCamera::get_logic_id() {
    return std::string("SmoothCamera");
}

sge::Vec2<float> SmoothCamera::lerp(sge::Vec2<float> current, sge::Vec2<float> target, float sharpness) {
    float x = lerp(current.x, target.x, sharpness);
    float y = lerp(current.y, target.y, sharpness);
    return sge::Vec2<float>(x, y);
}

SmoothCamera::SmoothCamera(GameObject_H target_go) {
    this->follow_go = target_go;
}

SmoothCamera::SmoothCamera() {
    this->follow_go = GameObject_H();
}

void SmoothCamera::update_target_zoom() {
    float zoom_dependernt_zoom_speed = ZOOM_SPEED*scene()->get_camera()->get_zoom()*env()->delta_time();
    if (env()->is_key_down(NG_CONTROLS_CAMERA_ZOOM_OUT)) {
        target_zoom += zoom_dependernt_zoom_speed;
    }

    if (env()->is_key_down(NG_CONTROLS_CAMERA_ZOOM_IN)) {
        target_zoom -= zoom_dependernt_zoom_speed;
    }
}


