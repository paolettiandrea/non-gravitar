#ifndef NON_GRAVITAR_PLAYERSPAWNMANAGER_HPP
#define NON_GRAVITAR_PLAYERSPAWNMANAGER_HPP


#include <SGE/logic/Logic.hpp>
#include <camera/follow/SmoothCamera.hpp>
#include "Player.hpp"

#define NG_PLAYER_SPAWN_LOOKBACK_TIME               3.0
#define NG_PLAYER_SPAWN_LOOKBACK_RESOLUTION         0.5
#define NG_PLAYER_SPAWN_TIME                        3.0

#define NG_PLAYER_SPAWN_PAST_POSITIONS_BUFFER_SIZE  ((int)(NG_PLAYER_SPAWN_LOOKBACK_TIME / NG_PLAYER_SPAWN_LOOKBACK_RESOLUTION))

/*!
 * \brief Manages the player spawn, death and respawn cycle.
 */
class PlayerSpawnManager : public sge::Logic {
public:
    PlayerSpawnManager(PlayerPersistentData *data, sge::Vec2<float> initial_spawn_point, SmoothCamera* camera_l);
    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

    Player* get_player_logic();

private:
    PlayerPersistentData *player_persistent_data;
    Player* player_l = nullptr;
    SmoothCamera* camera_l;


    sge::Vec2<float> past_positions_buffer[NG_PLAYER_SPAWN_PAST_POSITIONS_BUFFER_SIZE];
    float past_position_counter = 0;

    float respawn_counter = 0;

    sge::Vec2<float> initial_spawn_point;


    void spawn_player(sge::Vec2<float> pos);
};


#endif //NON_GRAVITAR_PLAYERSPAWNMANAGER_HPP
