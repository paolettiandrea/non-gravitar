#include "Trigger.hpp"

void Trigger::on_collision_begin(sge::CollisionInfo &collision_info) {
    if (collision_info.m_its_collider.is_valid()) {
        if (collision_info.m_its_collider->gameobject()->logichub()->has_logic(m_target_logic_id)) {
            on_collision_begin_event();
        }
    }
}

Trigger::Trigger(const std::string &target_logic_id) {
    m_target_logic_id = target_logic_id;
}

void Trigger::on_collision_end(sge::CollisionInfo &collision_info) {
    if (collision_info.m_its_collider.is_valid()) {
        if (collision_info.m_its_collider->gameobject()->logichub()->has_logic(m_target_logic_id)) {
            on_collision_end_event();
        }
    }
}

std::string Trigger::get_logic_id() {
    return std::string("Trigger");
}
