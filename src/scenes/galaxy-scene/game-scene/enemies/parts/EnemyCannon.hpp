#ifndef NON_GRAVITAR_ENEMYCANNON_HPP
#define NON_GRAVITAR_ENEMYCANNON_HPP

#include <SGE/utils/animation/Animation.hpp>
#include "EnemyPart.hpp"


#define SGE_ENEMY_EYE_COLOR sf::Color(30, 30, 30)
#define SGE_ENEMY_EYE_CLOSED_RADIUS 0.05
#define SGE_ENEMY_EYE_OPEN_RADIUS 0.15


class EnemyCannon : public EnemyPart {
public:
    EnemyCannon(EnemyPersistentData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data);

    std::string get_logic_id() override;

    void on_start() override;

};


#endif //NON_GRAVITAR_ENEMYCANNON_HPP
