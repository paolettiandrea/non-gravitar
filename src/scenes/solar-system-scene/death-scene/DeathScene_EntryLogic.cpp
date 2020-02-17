#include <SolarSystemScene_EntryLogic.hpp>
#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include <GameSceneEntryLogic.hpp>
#include "DeathScene_EntryLogic.hpp"

std::string DeathScene_EntryLogic::get_logic_id() {
    return std::string("DeathSceneEntryLogic");
}

void DeathScene_EntryLogic::on_update() {
    if (env()->is_key_pressed(sf::Keyboard::Q)) {
        env()->quit();
    }

    if (env()->is_key_pressed(sf::Keyboard::R)) {
        env()->doom_scenes(env()->get_scene_number());
        env()->book_new_scene_push("Restarted Game Scene", new GameScene_EntryLogic());
    }
}

void DeathScene_EntryLogic::on_start() {
    scene()->get_camera()->set_background_color(NG_BACKGROUND_COLOR);
    add_text("You died!", NG_MENU_FONT, 20, sf::Vector2f(0, 60));
    add_text("Total score: " + std::to_string(player_persistent_data->score.value() + player_persistent_data->bonus_score.value()), NG_MENU_FONT, 20, sf::Vector2f(0, 30));
    add_text("(R)estart or (Q)uit", NG_MENU_FONT, 15, sf::Vector2f(0, -30));
}

DeathScene_EntryLogic::DeathScene_EntryLogic(PlayerPersistentData *player_persistent_data) {
    this->player_persistent_data = player_persistent_data;
}




