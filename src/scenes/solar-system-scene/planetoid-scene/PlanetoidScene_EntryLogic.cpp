#include <Planetoid.hpp>
#include <OuterSpaceTransitionTrigger.hpp>
#include <scaled-planetoid/minimap/Minimap_UIContent.hpp>
#include "PlanetoidScene_EntryLogic.hpp"
#include <SGE/components/graphics/ui/UI.hpp>
#include <scaled-planetoid/minimap/Minimap.hpp>
#include <player/TractorBeam.hpp>
#include "SniperEnemyHead.hpp"
#include <player/PlayerSpawnManager.hpp>
#include <camera/follow/SmoothCamera.hpp>
#include <camera/follow/AutoZoomCamera.hpp>
#include "PauseLauncher.hpp"


std::string PlanetoidScene_EntryLogic::get_logic_id() {
    return "EntryLogic";
}

void PlanetoidScene_EntryLogic::on_start() {

    scene()->set_gravity(sge::Vec2<float>(0,0));
    scene()->get_camera()->set_background_color(NG_BACKGROUND_COLOR);

    gameobject()->logichub()->attach_logic(new PauseLauncher());

    // Spawn the planetoid (and relative enemies and crates)
    auto planetoid_go = scene()->spawn_gameobject("Planetoid");
    auto planetoid_l = new Planetoid(*planetoid_persistent_data, player_persistent_data);
    planetoid_go->logichub()->attach_logic(planetoid_l);

    auto entrance_pos = sge::Vec2<float>(planetoid_persistent_data->map_generator.entrance_coords.x,
                              planetoid_persistent_data->map_generator.entrance_coords.y);
    auto center_pos = sge::Vec2<float>(planetoid_persistent_data->size / 2.0, planetoid_persistent_data->size / 2.0);
    actual_radius = (entrance_pos - center_pos).get_magnitude();
    auto outward_dir = (entrance_pos - center_pos).normalize();
    auto spawn_point = entrance_pos + (outward_dir * (float)NG_PLANETOID_SCENE_SPAWN_DISTANCE);

    // Camera
    auto camera_l = new AutoZoomCamera(center_pos, (center_pos - entrance_pos).get_magnitude(), NG_CAMERA_TARGET_ZOOM);
    gameobject()->logichub()->attach_logic(camera_l);

    // Spawn the player
    auto player_spawn_manager_go = scene()->spawn_gameobject("PlayerSpawnManager");
    auto player_spawn_manager_l = new PlayerSpawnManager(player_persistent_data, spawn_point, camera_l);
    player_spawn_manager_go->logichub()->attach_logic(player_spawn_manager_l);

    auto player_l = player_spawn_manager_l->get_player_logic();
    auto player_go = player_l->gameobject();
    player_go->transform()->set_local_position(spawn_point);
    camera_l->set_follow(player_go);


    auto transition_handler = scene()->spawn_gameobject("TransitionHandler");
    auto planetoid_transition_handler_l = new PlanetoidTransitionHandler(parent_transition_handler, planetoid_l, base_miniature);
    transition_handler->logichub()->attach_logic(planetoid_transition_handler_l);

    auto transition_trigger = scene()->spawn_gameobject("TransitionTrigger");
    transition_trigger->transform()->set_local_position(center_pos);
    transition_trigger->logichub()->attach_logic(new OuterSpaceTransitionTrigger(actual_radius+NG_PLANETOID_SCENE_DOOM_DISTANCE_FROM_SURFACE*2,
                                                                                 planetoid_transition_handler_l, actual_radius+ NG_PLANETOID_SCENE_TELEPORT_DISTANCE_FROM_SURFACE,
                                                                                 player_spawn_manager_l));


    auto minimap_go = scene()->spawn_gameobject("Minimap");
    minimap_go->transform()->set_local_scale(0.5);
    minimap_go->logichub()->attach_logic(new Minimap(base_miniature, planetoid_l, player_spawn_manager_l));
}

PlanetoidScene_EntryLogic::PlanetoidScene_EntryLogic(PlanetoidPersistentData *planetoid_persistent_data, MiniaturePlanetoid* base_miniature, PlayerPersistentData* player_persistent_data, SceneTransitionHandler* parent_transition_handler) {
    this->planetoid_persistent_data = planetoid_persistent_data;
    this->base_miniature = base_miniature;
    this->player_persistent_data = player_persistent_data;
    this->parent_transition_handler = parent_transition_handler;
}
