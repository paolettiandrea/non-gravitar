#ifndef NON_GRAVITAR_ENEMY_HPP
#define NON_GRAVITAR_ENEMY_HPP


#include <scaled-planetoid/minimap/MinimapTraced_I.hpp>
#include "EnemyPersistentData.hpp"

#define SGE_ENEMY_VIEW_RANGE 30

#define SGE_ENEMY_BASIC_HEAD_COLOR sf::Color(202, 40, 27)
#define SGE_ENEMY_BASIC_BASE_COLOR sf::Color(255, 62, 47)


class Enemy : public sge::Logic {
public:
    Enemy(EnemyPersistentData *build_data);

    std::string get_logic_id() override;

    void on_start() override;

    void on_destruction() override;

protected:
    Rigidbody_H m_rigidbody;

    GameObject_H m_head_gameobject;
    GameObject_H m_base_gameobject;
    GameObject_H m_view_gameobject;

     EnemyPersistentData* build_data;
};


#endif //NON_GRAVITAR_ENEMY_HPP