#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include <COLORS.hpp>
#include "PlanetCompletedPrompt.hpp"

std::string PlanetCompletedPrompt::get_logic_id() {
    return std::string("PlanetCompletedPrompt");
}

void PlanetCompletedPrompt::on_start() {
    ui = gameobject()->add_component<sge::cmp::UI>("UI");
    auto text = new sge::UIText("You cleared the planetoid!\nPress ENTER to jump to Solar System", UI_FONT, 10);
    ui->set_content(text);
    ui->set_origin_alignment(sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP));
    ui->set_anchor_alignment(sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP));
    text->set_offset(sf::Vector2f(0, -100));


}

void PlanetCompletedPrompt::on_update() {
    if (env()->is_key_pressed(sf::Keyboard::Enter)) {
        key_pressed_ev_handler();
    }
}

PlanetCompletedPrompt::PlanetCompletedPrompt(Planetoid *planetoid, utils::event::EventHandler key_pressed_ev_handler) {
    this->key_pressed_ev_handler = key_pressed_ev_handler;
    this->planetoid = planetoid;
}


