
#include <follow/CameraFollow.hpp>
#include "../shooting/cannon/Cannon.hpp"
#include "Player.hpp"
#include <SGE/components/graphics/ui/UI.hpp>
#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include <SGE/components/graphics/ui/blocks/UIBar.hpp>

#include "MapGenerator.hpp"
#include "PlayerCannon.hpp"


std::string Player::get_logic_id() {
    return "Player";
}

void Player::on_start() {

    gameobject()->transform()->set_local_position(10,0);

    m_rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    m_rigidbody->set_fixed_rotation(true);

    auto player_body_go = scene()->spawn_gameobject("PlayerBody");
    player_body_go->transform()->set_parent(gameobject()->transform());
    m_body = new PlayerBody();
    player_body_go->logichub()->attach_logic(m_body);

    m_collider = gameobject()->add_component<sge::cmp::Collider>("Collider");
    m_collider->set_as_circle(0.5);


    gameobject()->logichub()->attach_logic(new CameraFollow(gameobject()));


    auto cannon_go = scene()->spawn_gameobject("Cannon");
    cannon_go->transform()->set_parent(player_body_go->transform());
    cannon_go->transform()->set_local_position(0, 1);
    cannon_go->logichub()->attach_logic(new PlayerCannon(30, m_rigidbody));

}

void Player::on_update() {


}
