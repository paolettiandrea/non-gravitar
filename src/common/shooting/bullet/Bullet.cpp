#include <SGE/components/graphics/VertArray.hpp>
#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include "Bullet.hpp"

std::string Bullet::get_logic_id() {
    return std::string("Bullet");
}

void Bullet::on_start() {
    auto vert_array = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    vert_array->import_smesh("./res/models/bullet__body.smesh");

    auto rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    auto collider = gameobject()->add_component<sge::cmp::Collider>("Collider");
    collider->load_spath("./res/models/bullet__collider.spath");
}

void Bullet::on_collision_begin(sge::CollisionInfo &collision_info) {
    if (collision_info.m_its_collider->get_rigidbody() != m_ignore_body && !collision_info.m_its_collider->is_sensor()) {
        gameobject()->doom();
    }

}

void Bullet::pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) {
    if (info.m_its_collider->get_rigidbody() == m_ignore_body) {
        contact->SetEnabled(false);
    }
}

Bullet::Bullet(utils::Handle<sge::cmp::Rigidbody> ignore_body) {
    m_ignore_body = ignore_body;
}
