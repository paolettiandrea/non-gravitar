#include "PlanetoidTransitionHandler.hpp"

std::string PlanetoidTransitionHandler::get_logic_id() {
    return std::string("PlanetoidTransitionHandler");
}

PlanetoidTransitionHandler::PlanetoidTransitionHandler(SceneTransitionHandler *parent_transition_handler)
        : SceneTransitionHandler(parent_transition_handler) {
}

void PlanetoidTransitionHandler::on_start() {
    SceneTransitionHandler::on_start();
    scene_transition_overlay_l->collapse();
}
