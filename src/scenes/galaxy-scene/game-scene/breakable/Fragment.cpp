#include <SGE/components/graphics/VertArray.hpp>
#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include "Fragment.hpp"

Fragment::Fragment(const FragmentInfo &info, unsigned int event_id) : info(info) {
    break_event_id = event_id;
}

void Fragment::on_start() {
    auto fragment_vert_array = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    fragment_vert_array->set_layer(info.fragment_render_layer);
    fragment_vert_array->set_primitive(sf::PrimitiveType::Triangles);
    sge::Path collider_path;
    for (int i = 0; i < 3; ++i) {
        auto local_position = sge::Vec2<float> (info.world_positions[i].first, info.world_positions[i].second) - info.world_center;
        fragment_vert_array->append_local_point(local_position);
        fragment_vert_array->set_vertex_color(i, info.colors[i]);
        collider_path.append_point(local_position);
    }
    collider_path.set_closed(true);

    auto fragment_collider = gameobject()->add_component<sge::cmp::Collider>("Collider");
    fragment_collider->set_as_polygon(collider_path);
}

std::string Fragment::get_logic_id() {
    return std::string("Fragment");
}

FragmentInfo Fragment::get_info() {
    return info;
}

void Fragment::pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) {
    auto fragment_logic = info.m_its_collider->gameobject()->logichub()->get_logic_by_id<Fragment>("Fragment");
    if (fragment_logic != nullptr) {
        if (fragment_logic->break_event_id == break_event_id) contact->SetEnabled(false);
    }
}
