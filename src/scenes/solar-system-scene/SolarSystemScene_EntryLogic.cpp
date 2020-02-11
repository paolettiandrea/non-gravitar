#include <Player.hpp>
#include <scaled-planetoid/MiniaturePlanetPortal.hpp>
#include <scene-transition/PlanetoidSceneTransitionTrigger.hpp>
#include <PauseLauncher.hpp>
#include <camera/follow/SmoothCamera.hpp>
#include <scene-transition/CompletionPrompt.hpp>
#include <camera/follow/AutoZoomCamera.hpp>
#include "SolarSystemScene_EntryLogic.hpp"

#define NG_SOLAR_SYSTEM_MINIATURE_PLANET_MIN_SIZE     10
#define NG_SOLAR_SYSTEM_MINIATURE_PLANET_MAX_SIZE     30

#define NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SIZE    150
#define NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SCALE   1.8f

// The definition of the planetoid, measured in grid_points per length unit
#define NG_SOLAR_SYSTEM_MINIATURE_PLANET_DEFINITION 3


std::string SolarSystemScene_EntryLogic::get_logic_id() {
    return std::string("SolarSystemScene_EntryLogic");
}


void SolarSystemScene_EntryLogic::on_start() {

    scene()->set_gravity(sge::Vec2<float>(0,0));

    gameobject()->logichub()->attach_logic(new PauseLauncher());

    SolarSystem_ConstructionData solar_sys_construction_data;
    solar_sys_construction_data.planetoid_number = NG_GAME_PLANETOID_NUMBER;
    solar_sys_construction_data.min_planetoid_size = NG_GAME_PLANETOID_MIN_SIZE;
    solar_sys_construction_data.max_planetoid_size = NG_GAME_PLANETOID_MAX_SIZE;

    auto player_l = new Player(player_persistent_data);

    // Transition handler
    GameObject_H scene_transition_handler = scene()->spawn_gameobject("Scene Transition Handler");
    auto* scene_transition_handler_l = new SolarSystemTransitionHandler(player_l);
    scene_transition_handler->logichub()->attach_logic(scene_transition_handler_l);

    // Player
    GameObject_H player = scene()->spawn_gameobject("Player");
    player->transform()->set_local_scale(2.f);
    player->logichub()->attach_logic(player_l);
    player_l->get_body_gameobject()->logichub()->attach_logic(new PlanetoidSceneTransitionTrigger(scene_transition_handler_l));

    // Planetoid Manager
    GameObject_H planetoid_manager = scene()->spawn_gameobject("Planetoid Manager");
    planetoid_manager_l = new PlanetoidManager(solar_sys_construction_data);
    planetoid_manager->logichub()->attach_logic(planetoid_manager_l);

    spawn_planets(solar_sys_construction_data, planetoid_manager_l->get_planetoid_data_vec());

    float scene_size = NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SIZE*NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SCALE;
    auto camera_l = new AutoZoomCamera(sge::Vec2<float>(0, 0), scene_size/20.f, scene_size*0.8f);
    gameobject()->logichub()->attach_logic(camera_l);
    camera_l->set_follow(player);


    on_completion_animation_ended_ev_handler = [&](){
        env()->doom_scenes(1);
    };
    on_completion_key_ev_handler = [=](){
        scene_transition_handler_l->start_transition_animation(&on_completion_animation_ended_ev_handler);
    };

    //scene_transition_handler_l->get_scene_transition_overlay()->collapse();

    //gameobject()->logichub()->attach_logic(new PauseLauncher());


    auto ui_go = scene()->spawn_gameobject("PlayerUI");
    PlayerUI* player_ui_l = new PlayerUI(player_persistent_data);
    ui_go->logichub()->attach_logic(player_ui_l);
}

void SolarSystemScene_EntryLogic::on_scene_resume() {
    int not_completed_counter = 0;
    for (auto planetoid_data : planetoid_manager_l->get_planetoid_data_vec()) {
        if (!planetoid_data->completed)  not_completed_counter++;
    }

    if (not_completed_counter==0) {
        auto completed_prompt = scene()->spawn_gameobject("Completion prompt");
        completed_prompt->logichub()->attach_logic(new CompletionPrompt(on_completion_key_ev_handler, "Congratulations you cleared the Solar System!\nPress ENTER to jump to the next one."));
    }
}

SolarSystemScene_EntryLogic::SolarSystemScene_EntryLogic(PlayerPersistentData *player_persistent_data) {
    this->player_persistent_data = player_persistent_data;
}

void SolarSystemScene_EntryLogic::spawn_planets(const SolarSystem_ConstructionData& solar_sys_construction_data, const std::vector<PlanetoidPersistentData *> &data_vec) {
    auto planetoid_data_vec = planetoid_manager_l->get_planetoid_data_vec();
    auto solar_system_size = NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SIZE * NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SCALE;


    NoiseMap noise_map(NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SIZE,NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SIZE);
    auto noise_map_half_size = NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SIZE / 2;
    Perlin perlin(NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SIZE / 5.f);
    perlin.simple_setup(1, 0.1, 1);
    perlin.fill_noise_map(noise_map, true);
    noise_map.apply_gradient_as_mask(CircularGradient(noise_map_half_size, noise_map_half_size*0.4f, noise_map_half_size, noise_map_half_size, 1.f, 0.3, new LinearInterpolator));
    int safe_distance = NG_SOLAR_SYSTEM_MINIATURE_PLANET_MAX_SIZE/NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SCALE;
    noise_map.apply_gradient_as_mask(CircularGradient(safe_distance, safe_distance-1, noise_map_half_size, noise_map_half_size, 0, 0.5, new LinearInterpolator));

    for (int i = 0; i < planetoid_data_vec.size(); ++i) {

        // Interpolate the target size of this planetoid miniature
        LinearInterpolator interpolator;
        float target_size = interpolator.interpolate((planetoid_data_vec[i]->size - solar_sys_construction_data.min_planetoid_size) /
                                                     ((float)(solar_sys_construction_data.max_planetoid_size - solar_sys_construction_data.min_planetoid_size)),
                                                     NG_SOLAR_SYSTEM_MINIATURE_PLANET_MIN_SIZE, NG_SOLAR_SYSTEM_MINIATURE_PLANET_MAX_SIZE);


        auto grid_size = planetoid_data_vec[i]->size / target_size / NG_SOLAR_SYSTEM_MINIATURE_PLANET_DEFINITION;

        GameObject_H new_scaled_planetoid = scene()->spawn_gameobject("Planetoid " + std::to_string(i));
        new_scaled_planetoid->logichub()->attach_logic(new MiniaturePlanetPortal(planetoid_data_vec[i], grid_size));
        new_scaled_planetoid->transform()->set_local_scale(1.0 / NG_SOLAR_SYSTEM_MINIATURE_PLANET_DEFINITION);


        // Find the position in the NoiseMap
        sge::Vec2<int> best_coord(-1, -1);
        float best_val = 0;
        for (int x = 0; x < NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SIZE; ++x) {
            for (int y = 0; y < NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SIZE; ++y) {
                if (noise_map[x][y] > best_val) {

                    best_val = noise_map[x][y];
                    best_coord = sge::Vec2<int>(x, y);
                }
            }
        }
        int this_planetoid_safe_distance = target_size/NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SCALE*1.2f;

        noise_map.apply_gradient_as_mask(CircularGradient(this_planetoid_safe_distance*2, this_planetoid_safe_distance, best_coord.x, best_coord.y, 0.f, 1.f, new LinearInterpolator));

        auto planetoid_pos = sge::Vec2<float>(
                best_coord.x * NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SCALE - solar_system_size / 2.f,
                best_coord.y * NG_SOLAR_SYSTEM_ARRANGEMENT_NOISE_MAP_SCALE - solar_system_size / 2.f);
        new_scaled_planetoid->transform()->set_local_position(planetoid_pos);
    }
}
