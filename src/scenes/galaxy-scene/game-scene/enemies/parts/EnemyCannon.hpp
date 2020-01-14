#ifndef NON_GRAVITAR_ENEMYCANNON_HPP
#define NON_GRAVITAR_ENEMYCANNON_HPP

#include <SGE/utils/animation/Animation.hpp>
#include <shooting/cannon/Cannon.hpp>
#include "EnemyPart.hpp"


class EnemyCannon : public EnemyPart {
public:
    EnemyCannon(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data);

    std::string get_logic_id() override;

    void on_start() override;

    void shoot(Bullet* bullet);

    void set_shooting_vel(float vel);

protected:
    Cannon* cannon_l;

};


#endif //NON_GRAVITAR_ENEMYCANNON_HPP
