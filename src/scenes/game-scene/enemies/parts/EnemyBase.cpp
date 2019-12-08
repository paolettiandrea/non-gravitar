#include <BreakTrigger.hpp>
#include "EnemyBase.hpp"

std::string EnemyBase::get_logic_id() {
    return std::string("EnemyBase");
}



EnemyBase::EnemyBase(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data)
        : EnemyPart(whole_data, my_breakable_geom_data) {}


