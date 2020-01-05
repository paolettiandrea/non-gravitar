#include "PlanetoidTransitionHandler.hpp"

std::string PlanetoidTransitionHandler::get_logic_id() {
    return std::string("PlanetoidTransitionHandler");
}

PlanetoidTransitionHandler::PlanetoidTransitionHandler(SceneTransitionHandler *parent_transition_handler)
        : SceneTransitionHandler(parent_transition_handler) {}
