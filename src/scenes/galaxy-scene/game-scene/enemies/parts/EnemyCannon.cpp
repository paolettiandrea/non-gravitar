#include <SGE/utils/interpolation/Interpolator.hpp>
#include <BreakGenerator.hpp>
#include "EnemyCannon.hpp"





string EnemyCannon::get_logic_id() {
    return std::string("EnemyEye");
}
void EnemyCannon::on_start() {
    EnemyPart::on_start();
    vertarray()->set_layer("enemy_cannon");
}

EnemyCannon::EnemyCannon(EnemyPersistentData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data)
        : EnemyPart(whole_data, my_breakable_geom_data) {}
