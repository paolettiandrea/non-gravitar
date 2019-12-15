#include "MiniaturePlanetPortal.hpp"

void MiniaturePlanetPortal::on_start() {
    MiniaturePlanetoid::on_start();

    m_rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    m_rigidbody->set_body_type(b2BodyType::b2_staticBody);
    for (int i = 0; i < m_scaled_marching_map->get_paths().size(); ++i) {
        auto new_wall = scene()->spawn_gameobject("Wall " + std::to_string(i));
        new_wall->transform()->set_parent(gameobject()->transform());
        auto wall_collider = new_wall->add_component<sge::cmp::Collider>("Collider");
        wall_collider->set_as_chain(m_scaled_marching_map->get_paths()[i]);
    }
}

std::string MiniaturePlanetPortal::get_logic_id() {
    return std::string("MiniaturePlanetPortal");
}

MiniaturePlanetPortal::MiniaturePlanetPortal(PlanetoidPersistentData *data, float grid_size)
: MiniaturePlanetoid(data, grid_size) {}
