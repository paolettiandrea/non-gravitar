#ifndef NON_GRAVITAR_ENEMY_HPP
#define NON_GRAVITAR_ENEMY_HPP


#include <scaled-planetoid/minimap/MinimapTraced_I.hpp>
#include <player/Player.hpp>
#include "EnemyBuildData.hpp"
#include "PlayerPersistentData.hpp"
#include "Trigger.hpp"

class Enemy : public sge::Logic {
public:
    Enemy(EnemyBuildData *build_data, PlayerPersistentData* player_persistent_data);

    std::string get_logic_id() override;

    void on_start() override;

    void on_destruction() override;

protected:
    Rigidbody_H m_rigidbody;

    GameObject_H m_head_gameobject;
    GameObject_H m_base_gameobject;
    GameObject_H m_view_gameobject;

     EnemyBuildData* build_data;
    PlayerPersistentData *player_persistent_data;

    Trigger<Player>* view_trigger;
};


#endif //NON_GRAVITAR_ENEMY_HPP
