#include <player/PlayerPersistentData.hpp>
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
    float rot_per_s = 2*M_PI;
    if (env()->is_key_down(sf::Keyboard::D)) {
        auto rot = gameobject()->transform()->get_world_rotation();
        auto b2_body = m_collider->get_rigidbody()->get_b2_body();
        b2_body->SetTransform(b2_body->GetPosition(), rot - rot_per_s*env()->fixed_delta_time());
    }
    if (env()->is_key_down(sf::Keyboard::A)) {
        auto rot = gameobject()->transform()->get_world_rotation();
        auto b2_body = m_collider->get_rigidbody()->get_b2_body();
        b2_body->SetTransform(b2_body->GetPosition(), rot + rot_per_s*env()->fixed_delta_time());
    }
}

void PlayerBody::on_fixed_update() {

}

PlayerBody::PlayerBody(PlayerPersistentData *player_persistent_data) {
    this->player_persistent_data = player_persistent_data;
}
