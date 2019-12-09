#include "PhysicsObject.hpp"

void PhysicsObject::on_start() {
    Logic::on_start();

    m_collider = gameobject()->add_component<sge::cmp::Collider>("Collider");
    m_collider->load_spath(physics_construction_data.get_collider_path());
    m_collider->set_material(physics_construction_data.get_physics_material());

    m_vertarray = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    m_vertarray->import_smesh(physics_construction_data.get_mesh_path());
}

VertArray_H PhysicsObject::vertarray() {
    return m_vertarray;
}

Collider_H PhysicsObject::collider() {
    return m_collider;
}

PhysicsObject::PhysicsObject(const PhysicsObject_ConstructionData &cd) : physics_construction_data(cd){
}

BreakableObject_ConstructionData::BreakableObject_ConstructionData(const std::string &truncated_load_path,
                                                                   unsigned int max_stuck_pieces_on_break) : PhysicsObject_ConstructionData(
        truncated_load_path), max_stuck_pieces_on_break(max_stuck_pieces_on_break) {}

unsigned int BreakableObject_ConstructionData::get_max_stuck_pieces_on_break() const {
    return max_stuck_pieces_on_break;
}

BreakableObject_ConstructionData::BreakableObject_ConstructionData(const std::string &truncated_load_path,
                                                                   const PhysicsMaterial &physics_material1,
                                                                   unsigned int max_stuck_pieces_on_break) : PhysicsObject_ConstructionData(
        truncated_load_path, physics_material1), max_stuck_pieces_on_break(max_stuck_pieces_on_break) {

}

