#include "PlayerSceneTransitionTrigger.hpp"

#include <SGE/components/physics/Collider.hpp>
#include <scaled-planetoid/MiniaturePlanetPortal.hpp>

std::string PlayerSceneTransitionTrigger::get_logic_id() {
    return std::string("PlayerGameSceneLauncher");
}

void PlayerSceneTransitionTrigger::on_collision_begin(sge::CollisionInfo &collision_info) {
    MiniaturePlanetPortal* miniature_planet = collision_info.m_its_collider->get_rigidbody()
            ->gameobject()->logichub()->get_logic_by_id<MiniaturePlanetPortal>("MiniaturePlanetPortal");
    if (miniature_planet != nullptr) {
        handler->launch_planetoid_scene(miniature_planet->get_planetoid_persistent_data(), miniature_planet);
    }
}

PlayerSceneTransitionTrigger::PlayerSceneTransitionTrigger(SceneTransitionHandler *transition_handler) {
    handler = transition_handler;
}
