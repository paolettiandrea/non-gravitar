#include "MultiShotEnemyHead.hpp"

MultiShotEnemyHead::MultiShotEnemyHead(EnemyPersistentData *whole_data,
                                       const BreakableObject_ConstructionData &my_breakable_geom_data) : EnemyHead(whole_data,
                                                                                                         my_breakable_geom_data) {}

string MultiShotEnemyHead::get_logic_id() {
    return std::string("MultiShotEnemyHead");
}



void MultiShotEnemyHead::on_start() {
    EnemyHead::on_start();
    right_cannon = assemble_cannon(-NG_ENEMY_MULTISHOT_CANNON_ANGLE);
    left_cannon = assemble_cannon(NG_ENEMY_MULTISHOT_CANNON_ANGLE);
}

void MultiShotEnemyHead::shoot() {
    EnemyHead::shoot();
    right_cannon->shoot(new Bullet(build_data->bullet_load_paths()));
    left_cannon->shoot(new Bullet(build_data->bullet_load_paths()));
}
