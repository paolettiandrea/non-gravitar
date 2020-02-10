#include "CompletionPrompt.hpp"
#include "PlanetoidTransitionHandler.hpp"

std::string PlanetoidTransitionHandler::get_logic_id() {
    return std::string("PlanetoidTransitionHandler");
}

PlanetoidTransitionHandler::PlanetoidTransitionHandler(SceneTransitionHandler *parent_transition_handler, Planetoid* planetoid, MiniaturePlanetoid* miniature_planetoid)
        : SceneTransitionHandler(parent_transition_handler) {
    this->planetoid = planetoid;
    this->miniature_planetoid = miniature_planetoid;
    planetoid->planetoid_destroyed_event += [&]() {
        build_completed_prompt();
    };
}

void PlanetoidTransitionHandler::pop_scene() {
    SceneTransitionHandler::pop_scene();
    miniature_planetoid->make_geometry_dirty();
}

void PlanetoidTransitionHandler::on_start() {
    SceneTransitionHandler::on_start();
    scene_transition_overlay_l->collapse();
    if (planetoid->get_enemy_counter() == 0) { build_completed_prompt(); }
}

void PlanetoidTransitionHandler::build_completed_prompt() {
    auto prompt_go = this->scene()->spawn_gameobject("Completed prompt");
    utils::event::EventHandler pop_ev_handler;
    pop_ev_handler = [&](){
        pop_scene();
    };
    prompt_go->logichub()->attach_logic(new CompletionPrompt(pop_ev_handler, "You cleared the planetoid!\nPress ENTER to jump to Solar System"));
}
