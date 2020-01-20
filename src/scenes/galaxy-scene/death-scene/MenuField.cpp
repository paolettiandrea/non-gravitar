#include "MenuField.hpp"

void MenuField::on_start() {
    auto ui = gameobject()->add_component<sge::cmp::UI>("UI");
    ui->set_anchor_alignment(anchor_alignment);
    ui->set_origin_alignment(origin_alignment);


    ui->set_content(text_content);

}

MenuField::MenuField(sge::UIText *m_text, sge::Alignment anchor_alignment, sge::Alignment origin_alignment) {
    text_content = m_text;
    this->anchor_alignment = anchor_alignment;
    this->origin_alignment = origin_alignment;
}


std::string MenuField::get_logic_id() {
    return std::string("MenuField");
}
