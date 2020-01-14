#include <SGE/components/graphics/VertArray.hpp>
#include <handler/BreakHandler.hpp>
#include <enemies/parts/EnemyBase.hpp>
#include "Enemy.hpp"
#include <EnemyHead.hpp>


std::string Enemy::get_logic_id() {
    return std::string("Enemy");
}

void Enemy::on_start() {
    m_rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    m_rigidbody->set_body_type(b2_kinematicBody);

    // Head - handles shooting
    m_head_gameobject = scene()->spawn_gameobject("Head");
    m_head_gameobject->transform()->set_parent(gameobject()->transform());
    m_head_gameobject->transform()->set_local_position(build_data->get_offsets().head_offset);
    auto head_logic = build_data->new_head_logic();
    m_head_gameobject->logichub()->attach_logic(head_logic);
    head_logic->vertarray()->set_color(build_data->get_enemy_palette()->primary);
    head_logic->vertarray()->set_layer("enemy_head");

    // Base
    m_base_gameobject = scene()->spawn_gameobject("Base");
    m_base_gameobject->transform()->set_parent(gameobject()->transform());
    auto base_logic = new EnemyBase(build_data, build_data->base_load_paths());
    m_base_gameobject->logichub()->attach_logic(base_logic);
    base_logic->vertarray()->set_color(build_data->get_enemy_palette()->dark);
    base_logic->vertarray()->set_layer("enemy_base");


    // View - handles the player detection
    m_view_gameobject = scene()->spawn_gameobject("View");
    m_view_gameobject->transform()->set_parent(gameobject()->transform());
    auto view_collider = m_view_gameobject->add_component<sge::cmp::Collider>("Collider");
    view_collider->set_sensor(true);
    view_collider->set_as_circle(build_data->get_view_range());
    view_trigger = new Trigger<Player>("Player");
    m_view_gameobject->logichub()->attach_logic(view_trigger);
    view_trigger->on_collision_begin_event += [=]() {
        head_logic->activate();
    };
    view_trigger->on_collision_end_event += [=]() {
        head_logic->deactivate();
    };


    gameobject()->logichub()->attach_logic(new BreakHandler(build_data->get_explosion_info(), true));
}

Enemy::Enemy(EnemyBuildData *build_data, PlayerPersistentData* player_persistent_data) {
    this->build_data = build_data;
    this->player_persistent_data = player_persistent_data;
}


void Enemy::on_destruction() {
    if (!scene()->is_doomed()) {
        build_data->destroyed = true;

        player_persistent_data->score.set(player_persistent_data->score.value() + 50);
    }
}
