#include <planetoids/PlanetoidManager.hpp>
#include <Player.hpp>
#include <scaled-planetoid/MiniaturePlanetPortal.hpp>
#include <scene-transition/PlanetoidSceneTransitionTrigger.hpp>
#include "GalaxyScene_EntryLogic.hpp"

#define NG_GALAXY_MINIATURE_PLANET_MIN_SIZE 10
#define NG_GALAXY_MINIATURE_PLANET_MAX_SIZE 30

// The definition of the planetoid, measured in grid_points per length unit
#define NG_GALAXY_MINIATURE_PLANET_DEFINITION 3


std::string GalaxyScene_EntryLogic::get_logic_id() {
    return std::string("GalaxyScene_EntryLogic");
}


void GalaxyScene_EntryLogic::on_start() {
    Galaxy_ConstructionData galaxy_construction_data;
    galaxy_construction_data.planetoid_number = 2;
    galaxy_construction_data.min_planetoid_size = 200;
    galaxy_construction_data.max_planetoid_size =700;

    auto player_l = new Player(&player_persistent_data);

    // Transition handler
    GameObject_H scene_transition_handler = scene()->spawn_gameobject("Scene Transition Handler");
    auto* scene_transition_handler_l = new SolarSystemTransitionHandler(player_l);
    scene_transition_handler->logichub()->attach_logic(scene_transition_handler_l);

    // Player
    GameObject_H player = scene()->spawn_gameobject("Player");
    player->logichub()->attach_logic(player_l);
    player_l->get_body_gameobject()->logichub()->attach_logic(new PlanetoidSceneTransitionTrigger(scene_transition_handler_l));

    // Planetoid Manager
    GameObject_H planetoid_manager = scene()->spawn_gameobject("Planetoid Manager");
    auto* planetoid_manager_l = new PlanetoidManager(galaxy_construction_data);
    planetoid_manager->logichub()->attach_logic(planetoid_manager_l);

    float temp_horizontal_anchor = 0;
    auto planetoid_data_vec = planetoid_manager_l->get_planetoid_data_vec();
    for (int i = 0; i < planetoid_data_vec.size(); ++i) {

        // Interpolate the target size of this planetoid miniature
        LinearInterpolator interpolator;
        float target_size = interpolator.interpolate((planetoid_data_vec[i]->size - galaxy_construction_data.min_planetoid_size) /
                ((float)(galaxy_construction_data.max_planetoid_size - galaxy_construction_data.min_planetoid_size)),
                NG_GALAXY_MINIATURE_PLANET_MIN_SIZE, NG_GALAXY_MINIATURE_PLANET_MAX_SIZE);


        auto grid_size = planetoid_data_vec[i]->size / target_size / NG_GALAXY_MINIATURE_PLANET_DEFINITION;

        LOG_INFO << "Target size" << target_size << ",\tGrid size: " << grid_size;

        GameObject_H new_scaled_planetoid = scene()->spawn_gameobject("Planetoid " + std::to_string(i));
        new_scaled_planetoid->logichub()->attach_logic(new MiniaturePlanetPortal(planetoid_data_vec[i], grid_size));
        new_scaled_planetoid->transform()->set_local_scale(1.0 / NG_GALAXY_MINIATURE_PLANET_DEFINITION);
        new_scaled_planetoid->transform()->set_local_position(temp_horizontal_anchor, 0);
        temp_horizontal_anchor+= 30;
    }
}
