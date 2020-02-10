#include "AutoZoomCamera.hpp"

std::string AutoZoomCamera::get_logic_id() {
    return std::string("AutoZoomCamera");
}

AutoZoomCamera::AutoZoomCamera(sge::Vec2<float> center, float radius, float base_zoom)  {
    this->center = center;
    this->radius = radius;
    this->base_zoom = base_zoom;
}


void AutoZoomCamera::update_target_zoom() {
    auto distance_from_center = scene()->get_camera()->get_center() - center;
    float calc_target_vert_zoom = (std::abs(distance_from_center.y) - radius + 20.f) * 2.f;
    float calc_target_hori_zoom = ((std::abs(distance_from_center.x) - radius + 20.f) * 2.f)/scene()->get_camera()->get_ratio();

    target_zoom = std::max(base_zoom, std::max(calc_target_hori_zoom, calc_target_vert_zoom));
}
