#ifndef NON_GRAVITAR_ENEMYPART_HPP
#define NON_GRAVITAR_ENEMYPART_HPP

#include "EnemyPersistentData.hpp"
#include "PhysicsObject.hpp"
#include "BreakGenerator.hpp"
#include "BreakTrigger.hpp"

class EnemyPart : public PhysicsObject{
public:
    EnemyPart(EnemyPersistentData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data);

    void on_start() override;

protected:
    EnemyPersistentData* build_data;

    BreakGenerator* break_generator_l;
    BreakTrigger* break_trigger_l;

};


#endif //NON_GRAVITAR_ENEMYPART_HPP
