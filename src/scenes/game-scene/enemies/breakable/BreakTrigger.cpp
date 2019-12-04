#include "BreakTrigger.hpp"
#include "BreakHandler.hpp"

BreakTrigger::BreakTrigger(float trigger_impact_vel) {
    m_trigger_impact_vel = trigger_impact_vel;
}

std::string BreakTrigger::get_logic_id() {
    return std::string("BreakTrigger");
}

void BreakTrigger::on_collision_begin(sge::CollisionInfo &collision_info) {
    Logic::on_collision_begin(collision_info);
    if (collision_info.get_impact_velocity().get_magnitude() > m_trigger_impact_vel) {
        // This object is breaking!

        // On break visit upstream the hierarchy and call the break pulse on the last child dependent BreakHandler
        utils::Handle<sge::GameObject> pointed_go = gameobject();
        BreakHandler* found_handler = nullptr;

        while (pointed_go.is_valid()) {
            auto pointed_handler_logic = pointed_go->logichub()->get_logic<BreakHandler>();
            if (pointed_handler_logic != nullptr && pointed_handler_logic->is_child_dependent()) found_handler = pointed_handler_logic;
            if (pointed_go->transform()->get_parent().is_valid()) pointed_go = pointed_go->transform()->get_parent()->gameobject();
            else break;
        }
        if (found_handler!= nullptr) {
            found_handler->break_pulse();
        } else {
            LOG_ERROR << "Couldn't find a BreakHandler up the hierarchy";
            exit(1);
        }
    }
}

void BreakTrigger::pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) {

}