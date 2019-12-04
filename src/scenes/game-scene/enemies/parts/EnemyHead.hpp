#ifndef NON_GRAVITAR_ENEMYHEAD_HPP
#define NON_GRAVITAR_ENEMYHEAD_HPP


#include <SGE/logic/Logic.hpp>
#include "EnemyPart.hpp"
#include "EnemyEye.hpp"

#define SGE_ENEMY_SHOT_PERIOD 1
#define SGE_ENEMY_MIN_ANGLE -M_PI_4
#define SGE_ENEMY_MAX_ANGLE M_PI_4

class EnemyHead : public EnemyPart {
    std::string get_logic_id() override;

public:
    EnemyHead(const std::string &mesh_file_path, const std::string &collider_file_path);

    void on_start() override;

    void activate();
    void deactivate();

    void on_update() override;

private:
    EnemyEye* m_eye;

    float m_shot_counter = 0;

    utils::Handle<sge::GameObject> player_collider;

    sge::Animation head_rotation_animation;

    utils::Handle<sge::GameObject> spinner_go;

    bool m_is_active = false;
};


#endif //NON_GRAVITAR_ENEMYHEAD_HPP
