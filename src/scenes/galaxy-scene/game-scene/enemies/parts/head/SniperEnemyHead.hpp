#ifndef NON_GRAVITAR_SNIPERENEMYHEAD_HPP
#define NON_GRAVITAR_SNIPERENEMYHEAD_HPP

#include "EnemyHead.hpp"

#define NG_ENEMY_SNIPER_LASER_RANGE 100

class SniperEnemyHead : public EnemyHead {
public:
    SniperEnemyHead(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data);

private:
    string get_logic_id() override;

protected:
    void shoot() override;
};


#endif //NON_GRAVITAR_SNIPERENEMYHEAD_HPP
