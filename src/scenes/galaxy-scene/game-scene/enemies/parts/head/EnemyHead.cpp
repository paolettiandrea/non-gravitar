#include "EnemyHead.hpp"
#include <random>
#include "Cannon.hpp"

std::string EnemyHead::get_logic_id() {
    return std::string("EnemyHead");
}

void EnemyHead::on_start() {
    EnemyPart::on_start();

    cannon_l = assemble_cannon(0);

    head_rotation_animation.on_animation_ended += [&]() {
        shoot();
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
            head_rotation_animation.set_to_val(get_shooting_angle());
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
: EnemyPart(whole_data, my_breakable_geom_data)
, head_rotation_animation(new LinearInterpolator(), 0, 0, whole_data->get_head_turning_duration()) {

}

void EnemyHead::shoot() {
    cannon_l->shoot(new Bullet(build_data->bullet_load_paths()));
}

EnemyCannon *EnemyHead::assemble_cannon(float rotation) {
    auto cannon_container = scene()->spawn_gameobject("Cannon Container");
    cannon_container->transform()->set_parent(gameobject()->transform());
    cannon_container->transform()->set_local_rotation(rotation);

    auto cannon_go= scene()->spawn_gameobject("Enemy Cannon");
    cannon_go->transform()->set_parent(cannon_container->transform());
    cannon_go->transform()->set_local_position(build_data->get_offsets().cannon_offset);
    auto cannon_logic = new EnemyCannon(build_data, build_data->cannon_load_paths());
    cannon_go->logichub()->attach_logic(cannon_logic);
    return cannon_logic;
}

float EnemyHead::get_shooting_angle() {
    return (((float)rand()) / RAND_MAX) * (SGE_ENEMY_MAX_ANGLE - SGE_ENEMY_MIN_ANGLE) + SGE_ENEMY_MIN_ANGLE;
}
