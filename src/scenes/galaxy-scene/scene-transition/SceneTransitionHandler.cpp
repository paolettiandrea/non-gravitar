#include <game-scene/PlanetoidScene_EntryLogic.hpp>
#include "SceneTransitionHandler.hpp"

SceneTransitionHandler::SceneTransitionHandler(Player *player_l) {
    player_logic = player_l;
}

void SceneTransitionHandler::launch_planetoid_scene(PlanetoidPersistentData *planetoid_persistent_data,
                                                    MiniaturePlanetoid *base_miniature) {
    env()->book_new_scene_push("Planetoid Scene", new PlanetoidScene_EntryLogic(planetoid_persistent_data, base_miniature, player_logic->get_persistent_data()));

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
}

std::string SceneTransitionHandler::get_logic_id() {
    return std::string("SceneTransitionHandler");
}
