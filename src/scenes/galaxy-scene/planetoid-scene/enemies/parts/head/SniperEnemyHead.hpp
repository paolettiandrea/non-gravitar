#ifndef NON_GRAVITAR_SNIPERENEMYHEAD_HPP
#define NON_GRAVITAR_SNIPERENEMYHEAD_HPP

#include "EnemyHead.hpp"
#include "enemies/parts/head/sniper/Laser.hpp"

#define NG_ENEMY_SNIPER_LASER_TIME_BEFORE_SHOOTING      1.0
#define NG_ENEMY_SNIPER_LASER_TIME_AFTER_SHOOTING       1.0


class SniperEnemyHead : public EnemyHead {
public:
    SniperEnemyHead(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data);

    void on_start() override;

    void on_update() override;


    static GameObject_H player_go;

private:
    string get_logic_id() override;

protected:
    void shoot() override;

    void spawn_laser();

    float get_shooting_angle() override;

    sge::Animation pause_animation;
};


#endif //NON_GRAVITAR_SNIPERENEMYHEAD_HPP
