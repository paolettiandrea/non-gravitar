#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include <breakable/handler/BreakHandler.hpp>
#include <breakable/generator/BreakGenerator.hpp>
#include "Bullet.hpp"

std::string Bullet::get_logic_id() {
    return std::string("Bullet");
}

void Bullet::on_start() {
    auto rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");

    PhysicsObject::on_start();

    vertarray()->set_layer("bullet");
    collider()->set_collision_category("Bullet");



    gameobject()->logichub()->attach_logic(new BreakHandler(true, true));
    gameobject()->logichub()->attach_logic(break_trigger);
    gameobject()->logichub()->attach_logic(new BreakGenerator(2));
}

void Bullet::on_collision_begin(sge::CollisionInfo &collision_info) {


}

void Bullet::pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) {
    if (info.m_its_collider->get_rigidbody() == m_ignore_body) {
        contact->SetEnabled(false);
    }
}

Bullet::Bullet(const PhysicsObject_ConstructionData& cd)
    : PhysicsObject(cd) {
    break_trigger = new BreakTrigger(2);
}

Rigidbody_H Bullet::get_ignored_body() const {
    return m_ignore_body;
}

void Bullet::set_ignore_body(Rigidbody_H ignore_body) {
    m_ignore_body = ignore_body;
    break_trigger->set_ignored_rb(ignore_body);
}
