#include "Player.hpp"
#include <SGE/components/graphics/ui/UI.hpp>
#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include "BreakHandler.hpp"
#include "BreakGenerator.hpp"
#include "DeathSceneEntryLogic.hpp"
#include "SmoothCamera.hpp"
#include "Bullet.hpp"
#include "COLORS.hpp"

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


    auto cannon_go = scene()->spawn_gameobject("Cannon");
    cannon_go->transform()->set_parent(player_body_go->transform());
    cannon_go->transform()->set_local_position(0, 1);
    player_cannon = new PlayerCannon(NG_PLAYER_CANNON_SHOOTING_VEL, m_rigidbody, persistent_data);
    cannon_go->logichub()->attach_logic(player_cannon);


    auto tractor_beam_go = scene()->spawn_gameobject("TractorBeam");
    tractor_beam_go->transform()->set_local_rotation(M_PI);
    tractor_beam_go->transform()->set_parent(player_body_go->transform());
    tractor_beam_go->logichub()->attach_logic(new TractorBeam());


    if (breakable) {
        ExplosionInfo explosion_info;
        explosion_info.explosion_radius = 1.0;
        explosion_info.explosion_force = 1.0;
        gameobject()->logichub()->attach_logic(new BreakHandler (explosion_info, true, true));
        trigger_l = new BreakTrigger(10, Rigidbody_H());
        trigger_l->on_break_event += [&]() {
            death();
        };
        player_body_go->logichub()->attach_logic(trigger_l);
        player_body_go->logichub()->attach_logic(new BreakGenerator(1));
    }

    persistent_data->is_alive = true;

    fuel_amount_changed_ev_handler = [=](){
        if (this->persistent_data->fuel_amount.value()<=0 && !this->scene()->is_doomed()) {
            this->game_over();
        }
    };
    persistent_data->fuel_amount.subscribe(fuel_amount_changed_ev_handler);
}

void Player::on_fixed_update() {
    if (env()->is_key_down(NG_CONTROLS_PLAYER_SHOOT_KEY)) {
        if (player_cannon->is_ready_to_shoot()) {
            auto bullet_l = new Bullet(PhysicsObject_ConstructionData("./res/models/enemies/basic/basic_cannon__bullet"));
            player_cannon->shoot(bullet_l);
            trigger_l->set_ignored_rb(bullet_l->collider()->get_rigidbody());
        }
    }
}

GameObject_H  Player::get_body_gameobject() const {
    return m_body->gameobject();
}

sge::Vec2<float> Player::get_position_relative_to_planetoid() {
    return gameobject()->transform()->get_world_position();
}

std::vector<sf::Vertex> Player::get_minimap_model_vertices() {
    sf::Color color(PLAYER_PALETTE.primary);
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

Player::Player(PlayerPersistentData *persistent_data, bool breakable) {
    this->persistent_data = persistent_data;
    this->breakable = breakable;
}

PlayerPersistentData *Player::get_persistent_data() {
    return persistent_data;
}

void Player::death() {
    LOG_DEBUG(1) << "Player is dead!";
    on_death_event();
    if (persistent_data->is_alive) {
        persistent_data->is_alive = false;
        if (persistent_data->lives.value()>1) {
            persistent_data->lives.set(persistent_data->lives.value() - 1);
        } else {
            game_over();
        }

    }
}

void Player::on_scene_destruction() {
    persistent_data->fuel_amount.unsubscribe(fuel_amount_changed_ev_handler);
}

void Player::game_over() {
    env()->doom_top_scene();
    env()->book_new_scene_push("Death scene", new DeathSceneEntryLogic(persistent_data));
}

