#include <Planetoid.hpp>
#include <OuterSpaceTransitionTrigger.hpp>
#include <scaled-planetoid/minimap/Minimap_UIContent.hpp>
#include "PlanetoidScene_EntryLogic.hpp"
#include <SGE/components/graphics/ui/UI.hpp>
#include <scaled-planetoid/minimap/Minimap.hpp>
#include <player/TractorBeam.hpp>


std::string PlanetoidScene_EntryLogic::get_logic_id() {
    return "EntryLogic";
}

void PlanetoidScene_EntryLogic::on_start() {

    scene()->set_gravity(sge::Vec2<float>(0,0));


    // Spawn the planetoid (and relative enemies and crates)
    auto planetoid_go = scene()->spawn_gameobject("Planetoid");
    auto planetoid_l = new Planetoid(*planetoid_persistent_data, player_persistent_data);
    planetoid_go->logichub()->attach_logic(planetoid_l);

    auto entrance_pos = sge::Vec2<float>(planetoid_persistent_data->map_generator.entrance_coords.x,
                              planetoid_persistent_data->map_generator.entrance_coords.y);
    auto center_pos = sge::Vec2<float>(planetoid_persistent_data->size / 2.0, planetoid_persistent_data->size / 2.0);
    auto outward_dir = (entrance_pos - center_pos).normalize();
    auto spawn_point = entrance_pos + (outward_dir * (float)NG_PLANETOID_SCENE_SPAWN_DISTANCE);

    // Spawn the player
    auto player_go = scene()->spawn_gameobject("Player");
    player_go->transform()->set_local_scale(0.5);
    player_go->transform()->set_local_position(spawn_point);
    auto player_l = new Player(player_persistent_data);
    player_go->logichub()->attach_logic(player_l);

    auto transition_trigger = scene()->spawn_gameobject("TransitionTrigger");
    transition_trigger->transform()->set_local_position(center_pos);
    transition_trigger->logichub()->attach_logic(new OuterSpaceTransitionTrigger(planetoid_persistent_data->size*2, base_miniature));

    auto minimap_go = scene()->spawn_gameobject("Minimap");
    minimap_go->transform()->set_local_scale(0.5);
    minimap_go->logichub()->attach_logic(new Minimap(base_miniature, planetoid_l, player_l));
}

PlanetoidScene_EntryLogic::PlanetoidScene_EntryLogic(PlanetoidPersistentData *planetoid_persistent_data, MiniaturePlanetoid* base_miniature, PlayerPersistentData* player_persistent_data) {
    this->planetoid_persistent_data = planetoid_persistent_data;
    this->base_miniature = base_miniature;
    this->player_persistent_data = player_persistent_data;
}
