#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include <COLORS.hpp>
#include "CompletionPrompt.hpp"

std::string CompletionPrompt::get_logic_id() {
    return std::string("PlanetCompletedPrompt");
}

void CompletionPrompt::on_start() {
    ui = gameobject()->add_component<sge::cmp::UI>("UI");
    auto text = new sge::UIText(prompt_string, UI_FONT, 10);
    ui->set_content(text);
    ui->set_origin_alignment(sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP));
    ui->set_anchor_alignment(sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP));
    text->set_offset(sf::Vector2f(0, -100));


}

void CompletionPrompt::on_update() {
    if (env()->is_key_pressed(sf::Keyboard::Enter)) {
        key_pressed_ev_handler();
    }
}

CompletionPrompt::CompletionPrompt(utils::event::EventHandler key_pressed_ev_handler, const std::string& prompt_string) {
    this->key_pressed_ev_handler = key_pressed_ev_handler;
    this->prompt_string = prompt_string;
}




