#include <SGE/components/physics/RayCastHandler.hpp>
#include <game-scene/enemies/parts/head/sniper/Laser.hpp>
#include "SniperEnemyHead.hpp"

string SniperEnemyHead::get_logic_id() {
    return std::string("SniperEnemyHead");
}

SniperEnemyHead::SniperEnemyHead(EnemyBuildData *whole_data,
                                 const BreakableObject_ConstructionData &my_breakable_geom_data)
                                 : EnemyHead(whole_data, my_breakable_geom_data) {}

void SniperEnemyHead::shoot() {
    EnemyHead::shoot();
    auto filter = collider()->get_filter_data();
    auto vec = sge::Vec2<float>::rotate(sge::Vec2<float>(0, 1), gameobject()->transform()->get_world_rotation());
    vec.set_magnitude(NG_ENEMY_SNIPER_LASER_RANGE);
    auto laser_end_pos = gameobject()->transform()->get_world_position() + vec;

//    sge::RayCastHandler handler(collider()->get_filter_data(), collider()->get_rigidbody(),
//                                gameobject()->transform()->get_world_position(), laser_end_pos);
//
//    scene()->raycast(&handler);
//
//    env()->debug_draw_line(handler.get_point_a(), handler.get_output().point, 5);

    auto laser_go = scene()->spawn_gameobject("Laser");
    LaserBuildData laser_build_data;
    laser_build_data.starting_pos = gameobject()->transform()->get_world_position();
    laser_build_data.ending_pos = laser_end_pos;
    laser_build_data.filter = filter;
    collider()->set_filter_collision_enabled_with(laser_build_data.filter, "Bullet", false);
    laser_build_data.ingore_rb = collider()->get_rigidbody();
    laser_build_data.duration = 3;
    laser_build_data.fade_in_duration = 0.5;
    laser_go->logichub()->attach_logic(new Laser(laser_build_data));
}
