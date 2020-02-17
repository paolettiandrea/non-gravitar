#include <player/PlayerPersistentData.hpp>
#include <utility-classes/Math.hpp>
#include "PlayerBody.hpp"

std::string PlayerBody::get_logic_id() {
    return "PlayerBody";
}

void PlayerBody::on_start() {
    // mesh
    m_vert_array = gameobject()->add_component<sge::cmp::VertArray>("VertArray");
    m_vert_array->import_smesh("./res/models/player/player_ship__body.smesh");
    m_vert_array->set_primitive(sf::PrimitiveType::Triangles);
    m_vert_array->set_color(PLAYER_PALETTE.primary);

    // collider
    m_collider = gameobject()->add_component<sge::cmp::Collider>("Collider");
    m_collider->load_spath("./res/models/player/player_ship__body_collider.spath");
    m_collider->set_collision_category("Player");
    m_collider->set_collision_enabled_with("Fading Fragment", false);

    // PlayerEngine
    auto engine_go = scene()->spawn_gameobject("PlayerEngine");
    engine_go->transform()->set_parent(gameobject()->transform());
    engine_go->logichub()->attach_logic(new PlayerEngine(m_collider->get_rigidbody(), player_persistent_data));
}

void PlayerBody::on_update() {
    if (env()->is_key_released(NG_CONTROLS_PLAYER_TURN_RIGHT_KEY) || env()->is_key_released(NG_CONTROLS_PLAYER_TURN_LEFT_KEY)) {
        current_rotation_vel = 0.f;
    }

    bool right_down = env()->is_key_down(NG_CONTROLS_PLAYER_TURN_RIGHT_KEY);
    bool left_down = env()->is_key_down(NG_CONTROLS_PLAYER_TURN_LEFT_KEY);

    if (right_down || left_down) {
        float blend = NG_PLAYER_ROTATION_SHARPNESS * env()->delta_time();
        current_rotation_vel = Math::lerp(current_rotation_vel, target_rotation_vel, blend);

        auto rot = gameobject()->transform()->get_world_rotation();
        auto b2_body = m_collider->get_rigidbody()->get_b2_body();
        if (right_down) { b2_body->SetTransform(b2_body->GetPosition(), rot - current_rotation_vel*env()->delta_time()); }
        if (left_down) { b2_body->SetTransform(b2_body->GetPosition(), rot + current_rotation_vel*env()->delta_time()); }
    }

}

PlayerBody::PlayerBody(PlayerPersistentData *player_persistent_data) {
    this->player_persistent_data = player_persistent_data;
}
