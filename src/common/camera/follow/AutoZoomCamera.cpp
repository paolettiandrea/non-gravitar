#include "AutoZoomCamera.hpp"

std::string AutoZoomCamera::get_logic_id() {
    return std::string("AutoZoomCamera");
}

AutoZoomCamera::AutoZoomCamera(sge::Vec2<float> center, float radius)  {
    this->center = center;
    this->radius = radius;
}


void AutoZoomCamera::update_target_zoom() {
    env()->debug_draw_circle(center, radius);
    auto distance_from_center = scene()->get_camera()->get_center() - center;
    float calc_target_vert_zoom = (std::abs(distance_from_center.y) - radius + 20.f) * 2.f;
    float calc_target_hori_zoom = ((std::abs(distance_from_center.x) - radius + 20.f) * 2.f)/scene()->get_camera()->get_ratio();

    target_zoom = std::max(NG_CAMERA_TARGET_ZOOM, std::max(calc_target_hori_zoom, calc_target_vert_zoom));
}
