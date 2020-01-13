#include <SGE/components/graphics/ui/UI.hpp>
#include "PlayerCannon.hpp"

PlayerCannon::PlayerCannon(float shooting_velocity, const Rigidbody_H &shooter_rigidbody)
        : Cannon(shooting_velocity, shooter_rigidbody) {}

void PlayerCannon::on_fixed_update() {

    stamina += NG_PLAYER_CANNON_STAMINA_REGEN_PER_SEC * env()->fixed_delta_time();
    if (stamina > max_stamina) stamina = max_stamina;

    if (stamina > NG_PLAYER_CANNON_STAMINA_COST_PER_SHOT && env()->is_key_down(sf::Keyboard::Space)) {

        auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_shot_time).count()/1000.0;

        if (passed > NG_PLAYER_CANNON_MIN_SHOT_FREQUENCY) {
            shoot(new Bullet(PhysicsObject_ConstructionData("./res/models/enemies/basic/basic_cannon__bullet")));
            last_shot_time = std::chrono::steady_clock::now();
            stamina -= NG_PLAYER_CANNON_STAMINA_COST_PER_SHOT;
        }
    }

    stamina_bar->set_bar(stamina/max_stamina);
}

void PlayerCannon::on_start() {
    Logic::on_start();

    last_shot_time = std::chrono::steady_clock::now();

    m_ui_component = gameobject()->add_component<sge::cmp::UI>("UI");
    m_ui_component->set_anchor_alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::BOTTOM);
    m_ui_component->set_origin_alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::BOTTOM);


    stamina_bar = new sge::UIBar(300, 20);
    stamina_bar->set_offset(sf::Vector2f(0, 50));

    m_ui_component->set_content(stamina_bar);
}


