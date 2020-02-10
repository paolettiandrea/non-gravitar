#include <GalaxyScene_EntryLogic.hpp>
#include "GameSceneEntryLogic.hpp"
#include "COLORS.hpp"

std::string GameScene_EntryLogic::get_logic_id() {
    return std::string("GameSceneEntryLogic");
}

void GameScene_EntryLogic::on_start() {
    scene()->get_camera()->set_background_color(PLAYER_PALETTE.primary);
    env()->book_new_scene_push("Solar System", new GalaxyScene_EntryLogic(&player_persistent_data));
}

void GameScene_EntryLogic::on_update() {
    env()->book_new_scene_push("Solar System", new GalaxyScene_EntryLogic(&player_persistent_data));
}
