#include <enemies/breakable/Breakable.hpp>
#include <enemies/breakable/BreakGenerator.hpp>
#include <enemies/breakable/BreakTrigger.hpp>
#include "EnemyHead.hpp"
#include <random>
#include "../../../../common/shooting/cannon/Cannon.hpp"

std::string EnemyHead::get_logic_id() {
    return std::string("EnemyHead");
}

EnemyHead::EnemyHead(const std::string &mesh_file_path, const std::string &collider_file_path) :
EnemyPart(mesh_file_path, collider_file_path)
, head_rotation_animation(new LinearInterpolator(), 0, 0, 0.5){}

void EnemyHead::on_start() {
    EnemyPart::on_start();
    spinner_go = scene()->spawn_gameobject("Spinner");
    spinner_go->transform()->set_parent(gameobject()->transform());
    auto eye_go = scene()->spawn_gameobject("Eye");
    eye_go->transform()->set_parent(spinner_go->transform());
    eye_go->transform()->set_local_position(sge::Vec2<float>(0, 1.5));
    m_eye = new EnemyEye();
    eye_go->logichub()->attach_logic(m_eye);

    auto cannon = new Cannon(20, 3);
    eye_go->logichub()->attach_logic(cannon);

    auto collider = get_collider();
    head_rotation_animation.on_animation_ended += [=]() {
        cannon->shoot(new Bullet(collider->get_rigidbody()));
    };
}

void EnemyHead::on_update() {
    float rotation = head_rotation_animation.step(env()->delta_time());
    if (gameobject()->transform()->get_local_rotation() != rotation) {
        spinner_go->transform()->set_local_rotation(rotation);
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
    m_eye->open_eye();

}

void EnemyHead::deactivate() {
    m_is_active = false;
    m_eye->close_eye();
    head_rotation_animation.stop();
}
