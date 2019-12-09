#include "CameraFollow.hpp"

std::string CameraFollow::get_logic_id() {
    return std::string("CameraFollow");
}

CameraFollow::CameraFollow(GameObject_H target) {
    m_target = target;
}

void CameraFollow::on_update() {
    scene()->get_camera()->set_center(m_target->transform()->get_world_position());


    float delta_time = env()->delta_time();

    float zoom_dependernt_zoom_speed = ZOOM_SPEED*scene()->get_camera()->get_zoom()*delta_time;


    if (env()->is_key_down(sf::Keyboard::LControl)) {
        scene()->get_camera()->offset_zoom(zoom_dependernt_zoom_speed);
    }

    if (env()->is_key_down(sf::Keyboard::LAlt)) {
        scene()->get_camera()->offset_zoom(-zoom_dependernt_zoom_speed);
    }
}
