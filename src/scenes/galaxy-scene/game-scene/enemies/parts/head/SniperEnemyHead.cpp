#include "SniperEnemyHead.hpp"
#include <SGE/components/physics/Rigidbody.hpp>

GameObject_H SniperEnemyHead::player_go = GameObject_H();

string SniperEnemyHead::get_logic_id() {
    return std::string("SniperEnemyHead");
}

SniperEnemyHead::SniperEnemyHead(EnemyBuildData *whole_data, const BreakableObject_ConstructionData &my_breakable_geom_data)
: EnemyHead(whole_data, my_breakable_geom_data)
, pause_animation(new LinearInterpolator(), 0, 0, NG_ENEMY_SNIPER_LASER_TIME_BEFORE_SHOOTING)
{

}

void SniperEnemyHead::shoot() {
    EnemyHead::shoot();
}

void SniperEnemyHead::on_update() {
    EnemyHead::on_update();

    if (pause_animation.is_active()) pause_animation.step(env()->fixed_delta_time());
}

void SniperEnemyHead::on_start() {
    EnemyHead::on_start();

    head_rotation_animation.on_animation_ended.clearSubscribers();
    head_rotation_animation.on_animation_ended += [&](){
        gameobject()->transform()->set_local_rotation(head_rotation_animation.get_to_val());
        spawn_laser();
        pause_animation.start();
    };

    pause_animation.on_animation_ended += [&]() {
        shoot();
    };

    cannon_l->set_shooting_vel(build_data->get_shooting_speed());
}

void SniperEnemyHead::spawn_laser() {
    auto filter = collider()->get_filter_data();
    auto vec = sge::Vec2<float>::rotate(sge::Vec2<float>(0, 1), gameobject()->transform()->get_world_rotation());
    vec.set_magnitude(build_data->get_view_range()*2);
    auto laser_end_pos = gameobject()->transform()->get_world_position() + vec;
    auto laser_go = scene()->spawn_gameobject("Laser");
    LaserBuildData laser_build_data;
    laser_build_data.starting_pos = gameobject()->transform()->get_world_position();
    laser_build_data.ending_pos = laser_end_pos;
    laser_build_data.filter = filter;
    collider()->set_filter_collision_enabled_with(laser_build_data.filter, "Bullet", false);
    laser_build_data.ingore_rb = collider()->get_rigidbody();
    laser_build_data.duration = NG_ENEMY_SNIPER_LASER_TIME_BEFORE_SHOOTING + NG_ENEMY_SNIPER_LASER_TIME_AFTER_SHOOTING;
    laser_build_data.fade_in_duration = 0.35;
    laser_go->logichub()->attach_logic(new Laser(laser_build_data));
}

float SniperEnemyHead::get_shooting_angle() {
    auto time_until_shooting = build_data->get_head_turning_duration() + NG_ENEMY_SNIPER_LASER_TIME_BEFORE_SHOOTING;

    auto player_rb = player_go->get_component<sge::cmp::Rigidbody>("Rigidbody");
    auto player_vel = player_rb->get_linear_velocity();

    auto future_player_pos = player_go->transform()->get_world_position() + player_vel*time_until_shooting;
    auto player_distance = (player_go->transform()->get_world_position() -
                            gameobject()->transform()->get_world_position()).get_magnitude();
    auto bullet_time = player_distance / build_data->get_shooting_speed();
    future_player_pos = future_player_pos + player_vel*bullet_time;     // just a rough approximation, there's no point in the enemy being too good

    float angle = sge::Vec2<float>::get_signed_angle(sge::Vec2<float>(0,1),
                                                      future_player_pos - gameobject()->transform()->get_world_position());


    angle -= gameobject()->transform()->get_parent()->get_world_rotation();

    while (angle > M_PI) { angle -= M_PI * 2; }
    while (angle < -M_PI) { angle += M_PI * 2; }

    angle = std::min(angle, build_data->get_max_shooting_angle());
    angle = std::max(angle, build_data->get_min_shooting_angle());

    return angle;

}
