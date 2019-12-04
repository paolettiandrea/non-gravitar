#include <enemies/breakable/BreakTrigger.hpp>
#include <enemies/breakable/BreakGenerator.hpp>
#include "EnemyPart.hpp"


EnemyPart::EnemyPart(const std::string &mesh_file_path, const std::string &collider_file_path) {
    this->mesh_file_path = mesh_file_path;
    this->collider_file_path = collider_file_path;
}

void EnemyPart::on_start() {
    Logic::on_start();

    m_collider = gameobject()->add_component<sge::cmp::Collider>("Collider");
    m_collider->load_spath(collider_file_path);

    m_vertarray = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    m_vertarray->import_smesh(mesh_file_path);

    gameobject()->logichub()->attach_logic(new BreakGenerator(3));
    gameobject()->logichub()->attach_logic(new BreakTrigger(10));
}


utils::Handle<sge::cmp::Collider> EnemyPart::get_collider() {
    return m_collider;
}

utils::Handle<sge::cmp::VertArray> EnemyPart::get_vertarray() {
    return m_vertarray;
}
