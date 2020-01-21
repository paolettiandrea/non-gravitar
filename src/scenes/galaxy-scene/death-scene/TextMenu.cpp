#include "TextMenu.hpp"


void TextMenu::add_text(std::string label, const std::string& font_id, unsigned int char_size, sf::Vector2f offset) {
    auto header_go = scene()->spawn_gameobject(label + " TextObject");
    header_go->transform()->set_parent(gameobject()->transform());
    auto header_ui = header_go->add_component<sge::cmp::UI>("UI");
    auto *header_text = new sge::UIText(label, font_id, char_size);
    header_ui->set_content(header_text);
    header_text->set_offset(offset);
}
