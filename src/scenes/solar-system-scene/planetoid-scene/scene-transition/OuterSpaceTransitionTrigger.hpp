#ifndef NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP
#define NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP


#include <SGE/logic/Logic.hpp>
#include <scaled-planetoid/MiniaturePlanetoid.hpp>
#include <scene-transition/PlanetoidTransitionHandler.hpp>
#include "PlayerSpawnManager.hpp"



#define NG_TRIGGER_COLLIDER_THICKNESS               20
#define NG_PLAYER_TELEPORT_DISTANCE_CHECK_PERIOD    0.5


class OuterSpaceTransitionTrigger : public sge::Logic {
public:
    explicit OuterSpaceTransitionTrigger(float doom_distance, PlanetoidTransitionHandler *planetoid_transition_handler,
                                         float player_teleport_radius, PlayerSpawnManager* player_spawn_manager);

    void on_start() override;

    std::string get_logic_id() override;

    void on_update() override;

private:
    float doom_distance;
    PlanetoidTransitionHandler *planetoid_transition_handler;
    PlayerSpawnManager* player_spawn_manager;
    PlayerPersistentData *player_persistent_data;
    float player_teleport_radius;
    float teleport_check_counter = 0;
};


#endif //NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP
