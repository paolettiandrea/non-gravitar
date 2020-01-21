#include <GalaxyScene_EntryLogic.hpp>
#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include "DeathSceneEntryLogic.hpp"

std::string DeathSceneEntryLogic::get_logic_id() {
    return std::string("DeathSceneEntryLogic");
}

void DeathSceneEntryLogic::on_update() {
    if (env()->is_key_pressed(sf::Keyboard::Q)) {
        env()->doom_scenes(2);
    }

    if (env()->is_key_pressed(sf::Keyboard::R)) {
        env()->doom_scenes(2);
        env()->book_new_scene_push("Solar System", new GalaxyScene_EntryLogic());
    }
}

void DeathSceneEntryLogic::on_start() {
    Logic::on_start();

    add_text("You died!", NG_MENU_FONT, 20, sf::Vector2f(0, 50));
    add_text("(R)estart or (Q)uit", NG_MENU_FONT, 15, sf::Vector2f(0, -30));
}




