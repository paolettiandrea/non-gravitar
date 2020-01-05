    #include "PlanetoidSceneTransitionTrigger.hpp"

#include <SGE/components/physics/Collider.hpp>
#include <scaled-planetoid/MiniaturePlanetPortal.hpp>

std::string PlanetoidSceneTransitionTrigger::get_logic_id() {
    return std::string("PlayerGameSceneLauncher");
}

void PlanetoidSceneTransitionTrigger::on_collision_begin(sge::CollisionInfo &collision_info) {
    MiniaturePlanetPortal* miniature_planet = collision_info.m_its_collider->get_rigidbody()
            ->gameobject()->logichub()->get_logic_by_id<MiniaturePlanetPortal>("MiniaturePlanetPortal");
    if (miniature_planet != nullptr) {
        handler->launch_planetoid_scene(miniature_planet);
    }
}

PlanetoidSceneTransitionTrigger::PlanetoidSceneTransitionTrigger(SolarSystemTransitionHandler *transition_handler) {
    handler = transition_handler;
}
