#include "BreakTrigger.hpp"
#include "BreakHandler.hpp"
#include <SGE/components//physics/Collider.hpp>

BreakTrigger::BreakTrigger(float trigger_impact_vel) {
    m_trigger_impact_vel = trigger_impact_vel;
}

std::string BreakTrigger::get_logic_id() {
    return std::string("BreakTrigger");
}

void BreakTrigger::on_collision_begin(sge::CollisionInfo &collision_info) {
    Logic::on_collision_begin(collision_info);

    if (break_triggered) {
        break_object();
    }
}

void BreakTrigger::pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) {
    if (info.get_impact_velocity().get_magnitude() > m_trigger_impact_vel) {
        if (!info.m_its_collider->is_sensor() && ignored_rigidbody != info.m_its_collider->get_rigidbody()) {
            if (!info.m_its_collider->get_rigidbody()->gameobject()->logichub()->has_logic("Fading")) {
                break_triggered = true;
                impact_vel_recorded_on_break = info.m_my_collider->get_rigidbody()->get_b2_body()->GetLinearVelocity();
            }
        }
    }
}

BreakTrigger::BreakTrigger(float trigger_impact_vel, Rigidbody_H ignored_rb) {
    m_trigger_impact_vel = trigger_impact_vel;
    ignored_rigidbody = ignored_rb;
}

void BreakTrigger::set_ignored_rb(Rigidbody_H rb) {
    ignored_rigidbody = rb;
}

void BreakTrigger::break_object() {
    on_break_event();
    // On break visit upstream the hierarchy and call the break pulse on the last child dependent BreakHandler
    GameObject_H pointed_go = gameobject();
    BreakHandler* found_handler = nullptr;

    while (pointed_go.is_valid()) {
        auto pointed_handler_logic = pointed_go->logichub()->get_logic<BreakHandler>();
        if (pointed_handler_logic != nullptr && pointed_handler_logic->is_child_dependent()) found_handler = pointed_handler_logic;
        if (pointed_go->transform()->get_parent().is_valid()) pointed_go = pointed_go->transform()->get_parent()->gameobject();
        else break;
    }
    if (found_handler!= nullptr) {
        found_handler->break_pulse(impact_vel_recorded_on_break, m_trigger_impact_vel);
    } else {
        LOG_ERROR << "Couldn't find a BreakHandler up the hierarchy";
        exit(1);
    }
}
