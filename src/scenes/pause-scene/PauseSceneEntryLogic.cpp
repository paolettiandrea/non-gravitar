#include "PauseSceneEntryLogic.hpp"

std::string PauseScene_EntryLogic::get_logic_id() {
    return std::string("PauseScene_EntryLogic");
}

void PauseScene_EntryLogic::on_start() {
    add_text("Game paused", NG_MENU_FONT, 20, sf::Vector2f(0, 50));
    add_text("(R)esume or (Q)uit", NG_MENU_FONT, 15, sf::Vector2f(0, -30));
}

void PauseScene_EntryLogic::on_update() {
    if (env()->is_key_pressed(sf::Keyboard::Q)) {
        env()->quit();
    }

    if (env()->is_key_pressed(sf::Keyboard::R)) {
        env()->doom_scenes(1);
    }
}
