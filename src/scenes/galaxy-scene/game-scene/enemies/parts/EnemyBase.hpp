#ifndef NON_GRAVITAR_ENEMYBASE_HPP
#define NON_GRAVITAR_ENEMYBASE_HPP


#include <SGE/logic/Logic.hpp>
#include "EnemyPart.hpp"

class EnemyBase : public EnemyPart {
public:
    EnemyBase(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data);

    std::string get_logic_id() override;

};


#endif //NON_GRAVITAR_ENEMYBASE_HPP
