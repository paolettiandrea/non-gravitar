#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include <CollisionTrigger.hpp>
#include "OuterSpaceTransitionTrigger.hpp"

OuterSpaceTransitionTrigger::OuterSpaceTransitionTrigger(float radius) {
    this->radius = radius;
}

void OuterSpaceTransitionTrigger::on_start() {
    auto rb = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    rb->set_body_type(b2BodyType::b2_staticBody);

    auto callback = [&](const sge::CollisionInfo& collision_info) {
        if (collision_info.m_its_collider->get_rigidbody()->gameobject()->logichub()->has_logic("Player")) {
            env()->doom_top_scene();
        }
    };

    for (int i = 0; i < 4; ++i) {
        GameObject_H trigger_go = scene()->spawn_gameobject("Trigger");
        trigger_go->transform()->set_parent(gameobject()->transform());
        CollisionTrigger* collision_trigger = new CollisionTrigger(callback);
        trigger_go->logichub()->attach_logic(collision_trigger);
        auto rotation = M_PI_2*i;
        auto offset = sge::Vec2<float>::rotate(sge::Vec2<float>(0, radius/2), rotation);
        trigger_go->transform()->set_local_position(offset);
        trigger_go->transform()->set_local_rotation(rotation);

        sge::Path path;
        path.append_point(sge::Vec2<float>(radius/2+NG_TRIGGER_COLLIDER_THICKNESS, 0));
        path.append_point(sge::Vec2<float>(radius/2+NG_TRIGGER_COLLIDER_THICKNESS, NG_TRIGGER_COLLIDER_THICKNESS));
        path.append_point(sge::Vec2<float>(-radius/2-NG_TRIGGER_COLLIDER_THICKNESS, NG_TRIGGER_COLLIDER_THICKNESS));
        path.append_point(sge::Vec2<float>(-radius/2-NG_TRIGGER_COLLIDER_THICKNESS, 0));
        path.set_closed(true);
        collision_trigger->collider->set_as_polygon(path);
    }
}

void OuterSpaceTransitionTrigger::on_collision_begin(sge::CollisionInfo &collision_info) {
    if (collision_info.m_its_collider->get_rigidbody()->gameobject()->logichub()->has_logic("Player")) {
        env()->doom_top_scene();
    }
}

std::string OuterSpaceTransitionTrigger::get_logic_id() {
    return std::string("OuterSpaceTransitionTrigger");
}
