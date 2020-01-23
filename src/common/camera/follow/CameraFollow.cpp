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




}
