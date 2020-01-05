#include <SGE/utils/interpolation/Interpolator.hpp>
#include "PlanetoidCorePortal.hpp"

std::string PlanetoidCorePortal::get_logic_id() {
    return std::string("PlanetoidCorePortal");
}

void PlanetoidCorePortal::on_start() {
    for (int i = 0; i < NG_PLANETOID_CORE_PORTAL_LAYER_NUMBER; ++i) {
        auto tri_go = scene()->spawn_gameobject("Triangle " + std::to_string(i));
        tri_go->transform()->set_parent(gameobject()->transform());
        triangles_gos[i] = tri_go;

        auto tri_vert_array = tri_go->add_component<sge::cmp::VertArray>("VertArray");
        tri_vert_array->set_primitive(sf::PrimitiveType::Triangles);

        auto t = ((float) i) / NG_PLANETOID_CORE_PORTAL_LAYER_NUMBER;

        LinearInterpolator interpolator;
        triangle_vels[i] = interpolator.interpolate(t, NG_PLANETOID_CORE_PORTAL_ROTATION_INNER_VEL,
                                                    NG_PLANETOID_CORE_PORTAL_ROTATION_OUTER_VEL);

        for (int j = 0; j < 3; ++j) {
            auto radius = interpolator.interpolate(t, NG_PLANETOID_CORE_PORTAL_MAX_RADIUS, NG_PLANETOID_CORE_PORTAL_MIN_RADIUS);
            tri_vert_array->append_local_point(
                    sge::Vec2<float>(std::cos(2 * M_PI / 3 * j) * radius, std::sin(2 * M_PI / 3 * j) * radius));
        }

        ColorInterpolator color_interpolator(new LinearInterpolator);
        tri_vert_array->set_color(color_interpolator.interpolate(t, NG_PLANETOID_CORE_PORTAL_ROTATION_TOP_COLOR,
                                                                 NG_PLANETOID_CORE_PORTAL_ROTATION_BOTTOM_COLOR));
    }
}


void PlanetoidCorePortal::on_update() {
    for (int i = 0; i < NG_PLANETOID_CORE_PORTAL_LAYER_NUMBER; ++i) {
        auto tri_trans = triangles_gos[i]->transform();
        tri_trans->set_local_rotation(tri_trans->get_local_rotation() + triangle_vels[i] * env()->delta_time());
    }
}
