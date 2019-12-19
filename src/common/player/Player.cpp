
#include <follow/CameraFollow.hpp>
#include "../shooting/cannon/Cannon.hpp"
#include "Player.hpp"
#include <SGE/components/graphics/ui/UI.hpp>
#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include <player/ui/PlayerUI.hpp>

#include "PlayerCannon.hpp"
#include "TractorBeam.hpp"


std::string Player::get_logic_id() {
    return "Player";
}

void Player::on_start() {
    m_rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    m_rigidbody->set_fixed_rotation(true);

    auto player_body_go = scene()->spawn_gameobject("PlayerBody");
    player_body_go->transform()->set_parent(gameobject()->transform());
    m_body = new PlayerBody(persistent_data);
    player_body_go->logichub()->attach_logic(m_body);


    gameobject()->logichub()->attach_logic(new CameraFollow(gameobject()));


    auto cannon_go = scene()->spawn_gameobject("Cannon");
    cannon_go->transform()->set_parent(player_body_go->transform());
    cannon_go->transform()->set_local_position(0, 1);
    cannon_go->logichub()->attach_logic(new PlayerCannon(30, m_rigidbody));


    auto tractor_beam_go = scene()->spawn_gameobject("TractorBeam");
    tractor_beam_go->transform()->set_local_rotation(M_PI);
    tractor_beam_go->transform()->set_parent(player_body_go->transform());
    tractor_beam_go->logichub()->attach_logic(new TractorBeam());


    auto ui_go = scene()->spawn_gameobject("PlayerUI");
    ui_go->transform()->set_parent(player_body_go->transform());
    ui_go->logichub()->attach_logic(new PlayerUI(persistent_data));


}

void Player::on_update() {


}

GameObject_H  Player::get_body_gameobject() const {
    return m_body->gameobject();
}

sge::Vec2<float> Player::get_position_relative_to_planetoid() {
    return gameobject()->transform()->get_world_position();
}

std::vector<sf::Vertex> Player::get_minimap_model_vertices() {
    sf::Color color(200, 200, 200);
    sf::Color secondary_color(color);
    secondary_color.a = 150;
    float size = 0.7;
    return {sf::Vertex(sf::Vector2f(size,size), color),
            sf::Vertex(sf::Vector2f(-size,size), color),
            sf::Vertex(sf::Vector2f(-size,-size), color),
            sf::Vertex(sf::Vector2f(size,-size), color),
            sf::Vertex(sf::Vector2f(size*2,size*2), secondary_color),
            sf::Vertex(sf::Vector2f(-size*2,size*2), secondary_color),
            sf::Vertex(sf::Vector2f(-size*2,-size*2), secondary_color),
            sf::Vertex(sf::Vector2f(size*2,-size*2), secondary_color)};
}

Player::Player(PlayerPersistentData *persistent_data) {
    this->persistent_data = persistent_data;
}

PlayerPersistentData *Player::get_persistent_data() {
    return persistent_data;
}
