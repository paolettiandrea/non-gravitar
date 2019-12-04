#include "EntryLogic.hpp"
#include "PlanetoidManager.hpp"


std::string EntryLogic::get_logic_id() {
    return "EntryLogic";
}

void EntryLogic::on_start() {
    // Spawn the player
    auto player_go = scene()->spawn_gameobject("Player");
    player_go->transform()->set_local_scale(0.5);
    player_go->logichub()->attach_logic(new Player());

    auto planetoid_manager_go = scene()->spawn_gameobject("Planetoid Manager");
    planetoid_manager_go->logichub()->attach_logic(new PlanetoidManager());
}
