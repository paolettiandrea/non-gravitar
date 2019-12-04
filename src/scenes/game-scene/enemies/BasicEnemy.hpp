#ifndef NON_GRAVITAR_BASICENEMY_HPP
#define NON_GRAVITAR_BASICENEMY_HPP


#include "Enemy.hpp"

#define SGE_ENEMY_VIEW_RANGE 30


class BasicEnemy : public Enemy {
public:

    static const sf::Color HEAD_COLOR;

    std::string get_logic_id() override;

    void on_start() override;

protected:
    utils::Handle<sge::GameObject> m_head_gameobject;
    utils::Handle<sge::GameObject> m_view_gameobject;
};


#endif //NON_GRAVITAR_BASICENEMY_HPP
