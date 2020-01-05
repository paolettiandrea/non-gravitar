#include <game-scene/PlanetoidScene_EntryLogic.hpp>
#include "SolarSystemTransitionHandler.hpp"


void SolarSystemTransitionHandler::launch_planetoid_scene(MiniaturePlanetoid *base_miniature) {

    if (scene_transition_overlay_l->get_radius_animation().is_done()) {
        if (launch_planetoid_callback) delete launch_planetoid_callback;

        launch_planetoid_callback = new utils::event::EventHandler();
        *launch_planetoid_callback = [=]() {
            env()->book_new_scene_push("Planetoid Scene", new PlanetoidScene_EntryLogic(base_miniature->get_planetoid_persistent_data(), base_miniature, player_logic->get_persistent_data(), this));

            auto planet_size_vec = sge::Vec2<float>(base_miniature->get_planetoid_persistent_data()->size,
                                                    base_miniature->get_planetoid_persistent_data()->size);
            auto portal_center = base_miniature->gameobject()->transform()->get_world_position() + planet_size_vec/base_miniature->get_grid_size()*base_miniature->gameobject()->transform()->get_world_scale().x/2.0;
            auto player_center = player_logic->gameobject()->transform()->get_world_position();
            auto diff = (player_center - portal_center).normalize();
            auto new_player_pos = player_center + (diff * 3.0);

            auto player_rb = player_logic->gameobject()->get_component<sge::cmp::Rigidbody>("Rigidbody");
            auto player_body = player_rb->get_b2_body();
            player_body->SetTransform(b2Vec2(new_player_pos.x, new_player_pos.y), player_body->GetAngle());
            player_body->SetLinearVelocity(b2Vec2(diff.x*NG_GALAXY_SCENE_TRANSITION_DRIFTING_VELOCITY, diff.y*NG_GALAXY_SCENE_TRANSITION_DRIFTING_VELOCITY));
        };
        start_transition_animation(launch_planetoid_callback);
    }
}

SolarSystemTransitionHandler::SolarSystemTransitionHandler(Player *player_l) : SceneTransitionHandler(nullptr) {
    player_logic = player_l;
}

std::string SolarSystemTransitionHandler::get_logic_id() {
    return std::string("SolarSystemTransitionHandler");
}
