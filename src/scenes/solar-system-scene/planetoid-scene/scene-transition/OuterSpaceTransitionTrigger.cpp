#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include <CollisionTrigger.hpp>
#include "OuterSpaceTransitionTrigger.hpp"

OuterSpaceTransitionTrigger::OuterSpaceTransitionTrigger(float doom_distance,
                                                         PlanetoidTransitionHandler *planetoid_transition_handler,
                                                         float player_teleport_radius, PlayerSpawnManager* player_spawn_manager) {
    this->doom_distance = doom_distance;
    this->planetoid_transition_handler = planetoid_transition_handler;
    this->player_spawn_manager = player_spawn_manager;
    this->player_teleport_radius = player_teleport_radius;
}

void OuterSpaceTransitionTrigger::on_start() {
    auto rb = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    rb->set_body_type(b2BodyType::b2_staticBody);

    player_persistent_data = player_spawn_manager->get_player_logic()->get_persistent_data();

    auto callback = [&](const sge::CollisionInfo& collision_info) {
        if (collision_info.m_its_collider->get_rigidbody()->gameobject()->logichub()->has_logic("Player")) {
            planetoid_transition_handler->pop_scene();

        } else {
            collision_info.m_its_collider->gameobject()->doom();
        }
    };

    for (int i = 0; i < 4; ++i) {
        GameObject_H trigger_go = scene()->spawn_gameobject("Trigger");
        trigger_go->transform()->set_parent(gameobject()->transform());
        CollisionTrigger* collision_trigger = new CollisionTrigger(callback);
        trigger_go->logichub()->attach_logic(collision_trigger);
        auto rotation = M_PI_2*i;
        auto offset = sge::Vec2<float>::rotate(sge::Vec2<float>(0, doom_distance / 2), rotation);
        trigger_go->transform()->set_local_position(offset);
        trigger_go->transform()->set_local_rotation(rotation);

        sge::Path path;
        path.append_point(sge::Vec2<float>(doom_distance / 2 + NG_TRIGGER_COLLIDER_THICKNESS, 0));
        path.append_point(sge::Vec2<float>(doom_distance / 2 + NG_TRIGGER_COLLIDER_THICKNESS, NG_TRIGGER_COLLIDER_THICKNESS));
        path.append_point(sge::Vec2<float>(-doom_distance / 2 - NG_TRIGGER_COLLIDER_THICKNESS, NG_TRIGGER_COLLIDER_THICKNESS));
        path.append_point(sge::Vec2<float>(-doom_distance / 2 - NG_TRIGGER_COLLIDER_THICKNESS, 0));
        path.set_closed(true);
        collision_trigger->collider->set_as_polygon(path);
    }
}

std::string OuterSpaceTransitionTrigger::get_logic_id() {
    return std::string("OuterSpaceTransitionTrigger");
}

void OuterSpaceTransitionTrigger::on_update() {
    teleport_check_counter += env()->delta_time();
    if (teleport_check_counter >= NG_PLAYER_TELEPORT_DISTANCE_CHECK_PERIOD) {
        teleport_check_counter -= NG_PLAYER_TELEPORT_DISTANCE_CHECK_PERIOD;
        if (player_persistent_data->is_player_alive()) {
            auto planetoid_half_size = planetoid_transition_handler->get_planetoid_data()->size / 2.f;
            auto distance = (sge::Vec2<float>(planetoid_half_size, planetoid_half_size) -
                             player_spawn_manager->get_player_logic()->gameobject()->transform()->get_world_position()).get_magnitude();
            if (distance > player_teleport_radius) {
                planetoid_transition_handler->pop_scene();
            }
        }

    }
}
