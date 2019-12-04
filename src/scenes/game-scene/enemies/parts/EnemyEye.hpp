#ifndef NON_GRAVITAR_ENEMYEYE_HPP
#define NON_GRAVITAR_ENEMYEYE_HPP

#include <SGE/utils/animation/Animation.hpp>
#include "EnemyPart.hpp"


#define SGE_ENEMY_EYE_COLOR sf::Color(30, 30, 30)
#define SGE_ENEMY_EYE_CLOSED_RADIUS 0.05
#define SGE_ENEMY_EYE_OPEN_RADIUS 0.15


class EnemyEye : public sge::Logic {
public:
    EnemyEye();

    std::string get_logic_id() override;

    void on_start() override;
    void on_update() override;

    void open_eye();
    void close_eye();


private:
    sge::Animation eye_wideness_animation;
    bool m_player_in_sight = false;

    utils::Handle<sge::cmp::VertArray> m_vert_array;
    utils::Handle<sge::cmp::Collider> m_collider;

    float last_displayed_width;

    void update_vert_array(float width);
};


#endif //NON_GRAVITAR_ENEMYEYE_HPP
