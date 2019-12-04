#include <SGE/components/graphics/VertArray.hpp>
#include <enemies/parts/EnemyHead.hpp>
#include <enemies/breakable/BreakHandler.hpp>
#include <enemies/parts/Trigger.hpp>
#include "BasicEnemy.hpp"

const sf::Color BasicEnemy::HEAD_COLOR = sf::Color(220, 80, 56);

std::string BasicEnemy::get_logic_id() {
    return std::string("BasicEnemy");
}

void BasicEnemy::on_start() {
    Enemy::on_start();

    m_rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    m_rigidbody->set_body_type(b2_kinematicBody);

    // Head - handles shooting
    m_head_gameobject = scene()->spawn_gameobject("Head");
    m_head_gameobject->transform()->set_parent(gameobject()->transform());
    auto head_logic = new EnemyHead("./res/models/enemies/basic_enemy__head.smesh","./res/models/enemies/basic_enemy__head_collider.spath");
    m_head_gameobject->logichub()->attach_logic(head_logic);
    head_logic->get_vertarray()->set_color(HEAD_COLOR);
    head_logic->get_vertarray()->set_layer("enemy1");

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
