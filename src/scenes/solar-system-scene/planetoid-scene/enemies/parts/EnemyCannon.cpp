#include <BreakGenerator.hpp>
#include "EnemyCannon.hpp"
#include "COLORS.hpp"



string EnemyCannon::get_logic_id() {
    return std::string("EnemyEye");
}
void EnemyCannon::on_start() {
    EnemyPart::on_start();
    vertarray()->set_layer("enemy_cannon");
    vertarray()->set_color(build_data->get_enemy_palette()->darker);
    auto offset_go = scene()->spawn_gameobject("Shooting offset");
    offset_go->transform()->set_local_position(build_data->get_offsets().shooting_offset);
    offset_go->transform()->set_parent(gameobject()->transform());

    cannon_l = new Cannon(build_data->get_shooting_speed(), collider()->get_rigidbody());
    offset_go->logichub()->attach_logic(cannon_l);
}

EnemyCannon::EnemyCannon(EnemyPersistentData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data)
        : EnemyPart(whole_data, my_breakable_geom_data) {
}

void EnemyCannon::shoot(Bullet *bullet) {
    cannon_l->shoot(bullet);
    break_trigger_l->set_ignored_rb(bullet->collider()->get_rigidbody());
}

void EnemyCannon::set_shooting_vel(float vel) { cannon_l->set_shooting_vel(vel); }

