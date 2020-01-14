#ifndef NON_GRAVITAR_ENEMYHEAD_HPP
#define NON_GRAVITAR_ENEMYHEAD_HPP


#include <SGE/logic/Logic.hpp>
#include <shooting/cannon/Cannon.hpp>
#include "EnemyPart.hpp"
#include "EnemyCannon.hpp"

#define SGE_ENEMY_SHOT_PERIOD       3
#define SGE_ENEMY_MIN_ANGLE         -M_PI_4
#define SGE_ENEMY_MAX_ANGLE         M_PI_4
#define SGE_ENEMY_SHOOTING_VEL      5

#define SGE_ENEMY_BASIC_CANNON_COLOR sf::Color(72, 34, 31)


class EnemyHead : public EnemyPart {
    std::string get_logic_id() override;

public:
    EnemyHead(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data);

    void on_start() override;

    void activate();
    void deactivate();

    void on_update() override;

protected:
    virtual void shoot();
    EnemyCannon* cannon_l;
    sge::Animation head_rotation_animation;

    EnemyCannon *assemble_cannon(float rotation);

    virtual float get_shooting_angle();

private:

    float m_shot_counter = 0;




    bool m_is_active = false;





};


#endif //NON_GRAVITAR_ENEMYHEAD_HPP
