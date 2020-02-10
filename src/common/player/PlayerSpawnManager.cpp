#include "SniperEnemyHead.hpp"
#include "PlayerUI.hpp"
#include "PlayerSpawnManager.hpp"

std::string PlayerSpawnManager::get_logic_id() {
    return std::string("PlayerSpawnManager");
}

void PlayerSpawnManager::on_start() {
    spawn_player(initial_spawn_point);

    auto ui_go = scene()->spawn_gameobject("PlayerUI");
    PlayerUI* player_ui_l = new PlayerUI(player_persistent_data);
    ui_go->logichub()->attach_logic(player_ui_l);
}

PlayerSpawnManager::PlayerSpawnManager(PlayerPersistentData *data, sge::Vec2<float> initial_spawn_point, SmoothCamera* camera_l) {
    this->player_persistent_data = data;
    this->initial_spawn_point = initial_spawn_point;
    this->camera_l = camera_l;
}

Player *PlayerSpawnManager::get_player_logic() {
    return player_l;
}

void PlayerSpawnManager::spawn_player(sge::Vec2<float> pos) {
    auto player_go = scene()->spawn_gameobject("Player");
    player_l = new Player(player_persistent_data, true);
    player_go->transform()->set_local_scale(0.4);
    player_go->transform()->set_local_position(pos);
    player_go->logichub()->attach_logic(player_l);
    SniperEnemyHead::player_go = player_go;
    player_l->on_death_event += [&](){
        player_l = nullptr;
    };

    camera_l->set_follow(player_go);
}

void PlayerSpawnManager::on_update() {
    past_position_counter += env()->delta_time();
    if (past_position_counter >= NG_PLAYER_SPAWN_LOOKBACK_RESOLUTION) {
        past_position_counter -= NG_PLAYER_SPAWN_LOOKBACK_RESOLUTION;
        for (int i = NG_PLAYER_SPAWN_PAST_POSITIONS_BUFFER_SIZE-2; i >= 0; --i) {
            past_positions_buffer[i + 1] = past_positions_buffer[i];
        }
        if (player_persistent_data->is_player_alive()) past_positions_buffer[0] = player_l->gameobject()->transform()->get_world_position();
        else past_positions_buffer[0] = past_positions_buffer[1];
    }

    if (!player_persistent_data->is_player_alive()) {
        respawn_counter += env()->delta_time();
        if (respawn_counter >= NG_PLAYER_SPAWN_TIME) {
            respawn_counter = 0;
            spawn_player(past_positions_buffer[NG_PLAYER_SPAWN_PAST_POSITIONS_BUFFER_SIZE - 1]);
        }
    }
    //env()->debug_draw_point(past_positions_buffer[NG_PLAYER_SPAWN_PAST_POSITIONS_BUFFER_SIZE - 1]);
}
