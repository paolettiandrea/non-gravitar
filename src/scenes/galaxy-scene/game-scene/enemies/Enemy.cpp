#include <SGE/components/graphics/VertArray.hpp>
#include <enemies/parts/EnemyHead.hpp>
#include <handler/BreakHandler.hpp>
#include <enemies/parts/Trigger.hpp>
#include <enemies/parts/EnemyBase.hpp>
#include "Enemy.hpp"


std::string Enemy::get_logic_id() {
    return std::string("Enemy");
}

void Enemy::on_start() {
    m_rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    m_rigidbody->set_body_type(b2_kinematicBody);

    // Head - handles shooting
    m_head_gameobject = scene()->spawn_gameobject("Head");
    m_head_gameobject->transform()->set_parent(gameobject()->transform());
    m_head_gameobject->transform()->set_local_position(build_data->head_offset());
    auto head_logic = new EnemyHead(build_data, build_data->head_load_paths());
    m_head_gameobject->logichub()->attach_logic(head_logic);
    head_logic->vertarray()->set_color(SGE_ENEMY_BASIC_HEAD_COLOR);
    head_logic->vertarray()->set_layer("enemy_head");

    // Base
    m_base_gameobject = scene()->spawn_gameobject("Base");
    m_base_gameobject->transform()->set_parent(gameobject()->transform());
    auto base_logic = new EnemyBase(build_data, build_data->base_load_paths());
    m_base_gameobject->logichub()->attach_logic(base_logic);
    base_logic->vertarray()->set_color(SGE_ENEMY_BASIC_BASE_COLOR);
    base_logic->vertarray()->set_layer("enemy_base");


    // View - handles the player detection
    m_view_gameobject = scene()->spawn_gameobject("View");
    m_view_gameobject->transform()->set_parent(gameobject()->transform());
    auto view_collider = m_view_gameobject->add_component<sge::cmp::Collider>("Collider");
    view_collider->set_sensor(true);
    view_collider->set_as_circle(SGE_ENEMY_VIEW_RANGE);
    auto view_trigger = new Trigger("Player");
    m_view_gameobject->logichub()->attach_logic(view_trigger);
    view_trigger->on_collision_begin_event += [=]() {
        head_logic->activate();
    };
    view_trigger->on_collision_end_event += [=]() {
        head_logic->deactivate();
    };

    gameobject()->logichub()->attach_logic(new BreakHandler(true));
}

Enemy::Enemy(EnemyPersistentData *build_data) {
    this->build_data = build_data;
}


void Enemy::on_destruction() {
    if (!scene()->is_doomed()) {
        build_data->destroyed = true;
    }
}
