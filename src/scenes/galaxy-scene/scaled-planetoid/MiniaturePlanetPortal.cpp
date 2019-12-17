#include "MiniaturePlanetPortal.hpp"

void MiniaturePlanetPortal::on_start() {
    MiniaturePlanetoid::on_start();

    m_rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    m_rigidbody->set_body_type(b2BodyType::b2_staticBody);
    auto wall_collider = gameobject()->add_component<sge::cmp::Collider>("Collider");
    wall_collider->set_as_chain(scaled_fog_background_marching_map->get_paths()[0]);

}

std::string MiniaturePlanetPortal::get_logic_id() {
    return std::string("MiniaturePlanetPortal");
}

MiniaturePlanetPortal::MiniaturePlanetPortal(PlanetoidPersistentData *data, float grid_size)
: MiniaturePlanetoid(data, grid_size) {}
