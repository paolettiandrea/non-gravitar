#ifndef NON_GRAVITAR_PLAYER_HPP
#define NON_GRAVITAR_PLAYER_HPP

#include "SGE/logic/Logic.hpp"

#include "SGE/components/graphics/VertArray.hpp"
#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include <player/ui/PlayerUI.hpp>
#include <SGE/components/graphics/ui/blocks/UIBar.hpp>
#include <scaled-planetoid/minimap/MinimapTraced_I.hpp>

#include "PlayerPersistentData.hpp"
#include "PlayerBody.hpp"
#include "PlayerCannon.hpp"


#include "CONTROLS.hpp"

#define NG_PLAYER_CANNON_SHOOTING_VEL       30


class Player : public sge::Logic, public MinimapTraced_I  {
public:
    explicit Player(PlayerPersistentData *persistent_data, bool breakable = false);
    std::string get_logic_id() override;

    void on_start() override;

    sge::Vec2<float> get_position_relative_to_planetoid() override;

    std::vector<sf::Vertex> get_minimap_model_vertices() override;

    utils::event::Event on_death_event;

    GameObject_H  get_body_gameobject() const;

    void on_fixed_update() override;

    PlayerPersistentData *get_persistent_data();

    void on_scene_destruction() override;

    void on_destruction() override;


private:
    bool breakable;
    BreakTrigger* trigger_l;
    Rigidbody_H m_rigidbody;
    Collider_H m_collider;

    PlayerBody* m_body;
    PlayerCannon *player_cannon;

    PlayerPersistentData *persistent_data;

    utils::event::EventHandler fuel_amount_changed_ev_handler;

    void death();

    void game_over();

};


#endif //NON_GRAVITAR_PLAYER_HPP
