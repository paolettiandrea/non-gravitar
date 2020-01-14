#include <SGE/components/physics/Rigidbody.hpp>
#include "Cannon.hpp"
#include <chrono>

std::string Cannon::get_logic_id() {
    return std::string("Cannon");
}

void Cannon::shoot(Bullet* bullet_logic) {
    auto bullet = scene()->spawn_gameobject("Bullet");
    bullet_logic->set_ignore_body(m_shooter_rigidbody);
    bullet->transform()->set_local_position(bullet->transform()->world_to_local_point(gameobject()->transform()->get_world_position()));
    bullet->transform()->set_local_rotation(gameobject()->transform()->get_world_rotation());

    bullet->logichub()->attach_logic(bullet_logic);
    auto bullet_rb = bullet->get_component<sge::cmp::Rigidbody>("Rigidbody");


    auto vel = sge::Vec2<float>::rotate(sge::Vec2<float>(0, m_shooting_vel),
                                        gameobject()->transform()->get_world_rotation());
    bullet_rb->get_b2_body()->SetLinearVelocity(b2Vec2(vel.x, vel.y) + m_shooter_rigidbody->get_b2_body()->GetLinearVelocity());
    bullet_rb->get_b2_body()->SetBullet(true);
}

Cannon::Cannon(float shooting_velocity, Rigidbody_H shooter_rigidbody) {
    m_shooting_vel = shooting_velocity;
    m_shooter_rigidbody = shooter_rigidbody;
}

void Cannon::set_shooting_vel(float vel) { m_shooting_vel = vel; }
