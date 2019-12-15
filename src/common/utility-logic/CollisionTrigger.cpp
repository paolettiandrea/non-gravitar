#include "CollisionTrigger.hpp"

std::string CollisionTrigger::get_logic_id() {
    return std::string("TriggerCollider");
}

CollisionTrigger::CollisionTrigger(const CollisionCallback& callback) {
    this->callback = callback;
}

void CollisionTrigger::on_start() {
    collider = gameobject()->add_component<sge::cmp::Collider>("Collider");
    collider->set_sensor(true);
}

void CollisionTrigger::on_collision_begin(sge::CollisionInfo &collision_info) {
    callback(collision_info);
}
