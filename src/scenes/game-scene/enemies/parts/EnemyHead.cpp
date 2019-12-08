#include <BreakTrigger.hpp>
#include "EnemyHead.hpp"
#include <random>
#include "Cannon.hpp"

std::string EnemyHead::get_logic_id() {
    return std::string("EnemyHead");
}

void EnemyHead::on_start() {
    EnemyPart::on_start();
    auto cannon_go = scene()->spawn_gameobject("Cannon");
    cannon_go->transform()->set_parent(gameobject()->transform());
    auto cannon_logic = new EnemyCannon(whole_data, whole_data->cannon_load_paths());
    cannon_go->logichub()->attach_logic(cannon_logic);
    cannon_logic->vertarray()->set_color(SGE_ENEMY_BASIC_CANNON_COLOR);
    auto cannon = new Cannon(5,  collider()->get_rigidbody());
    cannon_go->logichub()->attach_logic(cannon);

    head_rotation_animation.on_animation_ended += [=]() {
        cannon->shoot(new Bullet( whole_data->bullet_load_paths()));
    };
}

void EnemyHead::on_update() {
    float rotation = head_rotation_animation.step(env()->delta_time());
    if (gameobject()->transform()->get_local_rotation() != rotation) {
        gameobject()->transform()->set_local_rotation(rotation);
    }

    if (m_is_active) {
        m_shot_counter += env()->delta_time();
        if (m_shot_counter > SGE_ENEMY_SHOT_PERIOD) {
            m_shot_counter -= SGE_ENEMY_SHOT_PERIOD;
            head_rotation_animation.set_from_val(head_rotation_animation.get_val());
            auto random = (((float)rand()) / RAND_MAX) * (SGE_ENEMY_MAX_ANGLE - SGE_ENEMY_MIN_ANGLE) + SGE_ENEMY_MIN_ANGLE;
            head_rotation_animation.set_to_val(random);
            head_rotation_animation.start(true);
        }
    }
}

void EnemyHead::activate() {
    m_is_active = true;

}

void EnemyHead::deactivate() {
    m_is_active = false;
    head_rotation_animation.stop();
}

EnemyHead::EnemyHead(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data)
        : EnemyPart(whole_data, my_breakable_geom_data), head_rotation_animation(new LinearInterpolator(), 0, 0, 0.5) {}
