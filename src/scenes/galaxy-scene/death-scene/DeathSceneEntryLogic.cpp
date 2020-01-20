#include <GalaxyScene_EntryLogic.hpp>
#include "DeathSceneEntryLogic.hpp"
#include "MenuField.hpp"

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

    auto header_go = scene()->spawn_gameobject("Header");
    header_go->transform()->set_parent(gameobject()->transform());
    auto *header_text = new sge::UIText("You died!", NG_MENU_FONT, 20);
    header_text->set_offset(sf::Vector2f(0, 50));
    header_go->logichub()->attach_logic(new MenuField(header_text));

    auto options_go = scene()->spawn_gameobject("Options");
    options_go->transform()->set_parent(gameobject()->transform());
    auto *options_text = new sge::UIText("(R)estart or (Q)uit", NG_MENU_FONT, 15);
    options_text->set_offset(sf::Vector2f(0, -30));
    options_go->logichub()->attach_logic(new MenuField(options_text));
}
