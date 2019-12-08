#ifndef NON_GRAVITAR_ENEMYPART_HPP
#define NON_GRAVITAR_ENEMYPART_HPP

#include "PhysicsObject.hpp"
#include "BreakGenerator.hpp"
#include "BreakTrigger.hpp"
#include "EnemyBuildData.hpp"

class EnemyPart : public PhysicsObject{
public:
    EnemyPart(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data);

    void on_start() override;

protected:
    EnemyBuildData* whole_data;

private:
    BreakGenerator* break_generator_l;
    BreakTrigger* break_trigger_l;

};


#endif //NON_GRAVITAR_ENEMYPART_HPP
