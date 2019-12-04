#include <SGE/components/physics/Rigidbody.hpp>
#include "Cannon.hpp"
#include <chrono>

std::string Cannon::get_logic_id() {
    return std::string("Cannon");
}

void Cannon::on_fixed_update() {
    if (env()->is_key_down(sf::Keyboard::Space)) {
        float elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_last_shot_time).count();
        if (elapsed_millis > m_shooting_period) {
            //shoot();
            m_last_shot_time = std::chrono::steady_clock::now();
        }
    }
}

void Cannon::shoot(Bullet* bullet_logic) {
    auto bullet = scene()->spawn_gameobject("Bullet");
    bullet->transform()->set_local_position(bullet->transform()->world_to_local_point(gameobject()->transform()->get_world_position()));
    bullet->transform()->set_local_rotation(gameobject()->transform()->get_world_rotation());
    bullet->transform()->set_local_scale(0.1);

    bullet->logichub()->attach_logic(bullet_logic);
    auto bullet_rb = bullet->get_component<sge::cmp::Rigidbody>("Rigidbody");


    auto vel = sge::Vec2<float>::rotate(sge::Vec2<float>(0, m_shooting_vel),
                                        gameobject()->transform()->get_world_rotation());
    bullet_rb->get_b2_body()->SetLinearVelocity(b2Vec2(vel.x, vel.y));
    bullet_rb->get_b2_body()->SetBullet(true);
}

Cannon::Cannon(float shooting_velocity, float shooting_frequency) {
    m_shooting_vel = shooting_velocity;
    m_shooting_period = 1/shooting_frequency*1000;
}

void Cannon::on_start() {
    Logic::on_start();
    m_last_shot_time = std::chrono::steady_clock::now();
}
