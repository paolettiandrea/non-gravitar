#include <game-scene/PlanetoidScene_EntryLogic.hpp>
#include "SceneTransitionHandler.hpp"

SceneTransitionHandler::SceneTransitionHandler(Player *player_l) {
    player_logic = player_l;
}

void SceneTransitionHandler::launch_planetoid_scene(PlanetoidPersistentData *planetoid_persistent_data,
                                                    MiniaturePlanetoid *base_miniature) {
    env()->book_new_scene_push("Planetoid Scene", new PlanetoidScene_EntryLogic(planetoid_persistent_data, base_miniature));
}

std::string SceneTransitionHandler::get_logic_id() {
    return std::string("SceneTransitionHandler");
}
