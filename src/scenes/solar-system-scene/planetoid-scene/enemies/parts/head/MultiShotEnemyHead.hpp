#ifndef NON_GRAVITAR_MULTISHOTENEMYHEAD_HPP
#define NON_GRAVITAR_MULTISHOTENEMYHEAD_HPP


#include "EnemyHead.hpp"

#define NG_ENEMY_MULTISHOT_CANNON_ANGLE 2*M_PI/7

class MultiShotEnemyHead : public EnemyHead {
public:
    MultiShotEnemyHead(EnemyPersistentData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data);

    string get_logic_id() override;

    void on_start() override;

protected:
    void shoot() override;

protected:
    EnemyCannon* right_cannon;
    EnemyCannon* left_cannon;
};


#endif //NON_GRAVITAR_MULTISHOTENEMYHEAD_HPP
