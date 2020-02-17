#include <Player.hpp>
#include <scaled-planetoid/MiniaturePlanetPortal.hpp>
#include <scene-transition/PlanetoidSceneTransitionTrigger.hpp>
#include <PauseLauncher.hpp>
#include <camera/follow/SmoothCamera.hpp>
#include <scene-transition/CompletionPrompt.hpp>
#include <camera/follow/AutoZoomCamera.hpp>
#include <random>
#include "SolarSystemScene_EntryLogic.hpp"

#define NG_SOLAR_SYSTEM_MINIATURE_PLANET_MIN_SIZE     10
#define NG_SOLAR_SYSTEM_MINIATURE_PLANET_MAX_SIZE     30


#define NG_SOLAR_SYSTEM_ARRANGEMENT_RADIUS_VARIABILITY  0.3f
#define NG_SOLAR_SYSTEM_ARRANGEMENT_RADIUS_MULTIPLIER   1.5f

// The definition of the planetoid miniature, measured in grid_points per length unit
#define NG_SOLAR_SYSTEM_MINIATURE_PLANET_DEFINITION 3


std::string SolarSystemScene_EntryLogic::get_logic_id() {
    return std::string("SolarSystemScene_EntryLogic");
}


void SolarSystemScene_EntryLogic::on_start() {
    scene()->get_camera()->set_background_color(NG_BACKGROUND_COLOR);
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

    float safe_circumference = planetoid_manager_l->get_planetoid_data_vec().size() * NG_SOLAR_SYSTEM_MINIATURE_PLANET_MAX_SIZE;
    float safe_radius = safe_circumference / (2 * M_PI);
    float actual_radius = safe_radius * NG_SOLAR_SYSTEM_ARRANGEMENT_RADIUS_MULTIPLIER;
    spawn_planets(solar_sys_construction_data, actual_radius);

    auto camera_l = new AutoZoomCamera(sge::Vec2<float>(0, 0), actual_radius, actual_radius*3);
    gameobject()->logichub()->attach_logic(camera_l);
    camera_l->set_follow(player);


    on_completion_animation_ended_ev_handler = [&](){
        env()->doom_scenes(1);
    };
    on_completion_key_ev_handler = [=](){
        scene_transition_handler_l->start_transition_animation(&on_completion_animation_ended_ev_handler);
    };


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

void SolarSystemScene_EntryLogic::spawn_planets(const SolarSystem_ConstructionData& solar_sys_construction_data, float safe_radius) {
    auto planetoid_data_vec = planetoid_manager_l->get_planetoid_data_vec();

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    auto random_angle_gen = std::uniform_real_distribution<float>(0, M_PI_2);

    float angle = random_angle_gen(gen);
    auto random_radius_gen = std::uniform_real_distribution<float>(0, safe_radius*NG_SOLAR_SYSTEM_ARRANGEMENT_RADIUS_VARIABILITY);

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

        float radius_offset = random_radius_gen(gen);
        if (i%2==0) radius_offset = -radius_offset;
        auto actual_radius = safe_radius + radius_offset;
        auto planetoid_pos = (sge::Vec2<float>(std::cos(angle), std::sin(angle)) * actual_radius) - sge::Vec2<float>(target_size/2, target_size/2);
        new_scaled_planetoid->transform()->set_local_position(planetoid_pos);

        angle += 2.f * M_PI / planetoid_data_vec.size();
    }
}
