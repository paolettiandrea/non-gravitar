#include "SceneTransitionHandler.hpp"


void SceneTransitionHandler::start_transition_animation(utils::event::EventHandler* post_animation_callback) {
    scene_transition_overlay_l->expand(post_animation_callback);
}

void SceneTransitionHandler::on_start() {
    Logic::on_start();
    scene_transition_overlay_l = new SceneTransitionOverlay(new LinearInterpolator, 0.5);

    gameobject()->logichub()->attach_logic(scene_transition_overlay_l);

    pop_callback = [&](){
        scene()->doom_scene();
        if (parent_transition_handler) {
            parent_transition_handler->scene_transition_overlay_l->collapse();
        }
    };
}

SceneTransitionHandler::SceneTransitionHandler(SceneTransitionHandler *parent_transition_handler) {
    this->parent_transition_handler = parent_transition_handler;
}

void SceneTransitionHandler::pop_scene() {
    start_transition_animation(&pop_callback);
}
