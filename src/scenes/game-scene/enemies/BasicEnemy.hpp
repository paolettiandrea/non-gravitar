#ifndef NON_GRAVITAR_BASICENEMY_HPP
#define NON_GRAVITAR_BASICENEMY_HPP


#include "EnemyBuildData.hpp"

#define SGE_ENEMY_VIEW_RANGE 30

#define SGE_ENEMY_BASIC_HEAD_COLOR sf::Color(202, 40, 27)
#define SGE_ENEMY_BASIC_BASE_COLOR sf::Color(255, 62, 47)


class BasicEnemy : public sge::Logic {
public:
    BasicEnemy(EnemyBuildData *build_data);

    std::string get_logic_id() override;

    void on_start() override;

protected:
    utils::Handle<sge::cmp::Rigidbody> m_rigidbody;

    utils::Handle<sge::GameObject> m_head_gameobject;
    utils::Handle<sge::GameObject> m_base_gameobject;
    utils::Handle<sge::GameObject> m_view_gameobject;

     EnemyBuildData* build_data;
};


#endif //NON_GRAVITAR_BASICENEMY_HPP
