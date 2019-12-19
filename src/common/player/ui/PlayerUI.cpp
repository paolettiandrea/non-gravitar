#include <iomanip>
#include <iostream>

#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include "PlayerUI.hpp"
#include "PlayerLivesIndicator.hpp"

std::string PlayerUI::get_logic_id() {
    return std::string("PlayerUI");
}

PlayerUI::PlayerUI(PlayerPersistentData *player_persistent_data) : score_animation(new LinearInterpolator, 0, 0, NG_PLAYER_UI_SCORE_ANIMATION_DURATION) {
    this->player_persistent_data = player_persistent_data;
}

void PlayerUI::on_start() {
    // SCORE
    auto score_go = scene()->spawn_gameobject("Score UI");
    score_go->transform()->set_parent(gameobject()->transform());
    auto score_ui = score_go->add_component<sge::cmp::UI>("UI");
    auto score_header_content = new sge::UIText("SCORE", NG_PLAYER_UI_SCORE_FONT_ID, NG_PLAYER_UI_SCORE_HEADER_CHAR_SIZE);
    score_header_content->set_offset(sf::Vector2f(0, -NG_PLAYER_UI_VERTICAL_PADDING));
    score_ui->set_content(score_header_content);
    score_ui->set_anchor_alignment(sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP));
    score_ui->set_origin_alignment(sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP));

    auto score_text_go = scene()->spawn_gameobject("Score Text");
    score_text_go->transform()->set_parent(gameobject()->transform());
    auto score_text_ui = score_text_go->add_component<sge::cmp::UI>("UI");
    score_text_ui->set_anchor_alignment(sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP));
    score_text_ui->set_origin_alignment(sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP));
    score_text = new sge::UIText(get_string_with_leading_zeros(player_persistent_data->score.value(), NG_PLAYER_SCORE_NUMBER_OF_DIGITS), NG_PLAYER_UI_SCORE_FONT_ID, NG_PLAYER_UI_SCORE_AMOUNT_CHAR_SIZE);
    score_text_ui->set_content(score_text);
    score_text->set_offset(sf::Vector2f(0, -NG_PLAYER_UI_VERTICAL_PADDING - NG_PLAYER_UI_SCORE_HEADER_CHAR_SIZE - NG_PLAYER_UI_SCORE_SPACING));

    score_changed_ev_handler = [&]() {
        score_animation.set_from_val(represented_score_val);
        score_animation.set_to_val(player_persistent_data->score.value());
        score_animation.start();
    };

    player_persistent_data->score.subscribe(score_changed_ev_handler);


    // LIVES
    auto lives_header = scene()->spawn_gameobject("Lives header UI");
    lives_header->transform()->set_parent(gameobject()->transform());
    auto lives_header_ui = lives_header->add_component<sge::cmp::UI>("UI");
    auto lives_header_text_content = new sge::UIText("LIVES", NG_PLAYER_UI_SCORE_FONT_ID, NG_PLAYER_UI_SCORE_HEADER_CHAR_SIZE);
    lives_header_text_content->set_offset(sf::Vector2f(-NG_PLAYER_UI_HORIZONTAL_PADDING, -NG_PLAYER_UI_VERTICAL_PADDING));
    lives_header_ui->set_content(lives_header_text_content);
    lives_header_ui->set_anchor_alignment(sge::Alignment(sge::HotizontalAlignment::LEFT, sge::VerticalAlignment::TOP));
    lives_header_ui->set_origin_alignment(sge::Alignment(sge::HotizontalAlignment::LEFT, sge::VerticalAlignment::TOP));

    auto lives_indicator = scene()->spawn_gameobject("Lives header UI");
    lives_indicator->transform()->set_parent(gameobject()->transform());
    auto lives_indicator_ui = lives_indicator->add_component<sge::cmp::UI>("UI");
    auto lives_indicator_content = new PlayerLivesIndicator(player_persistent_data->lives.value());
    lives_indicator_content->set_offset(sf::Vector2f(-NG_PLAYER_UI_HORIZONTAL_PADDING, -NG_PLAYER_UI_VERTICAL_PADDING - NG_PLAYER_UI_SCORE_HEADER_CHAR_SIZE - NG_PLAYER_UI_SCORE_SPACING));
    lives_indicator_ui->set_content(lives_indicator_content);
    lives_indicator_ui->set_anchor_alignment(sge::Alignment(sge::HotizontalAlignment::LEFT, sge::VerticalAlignment::TOP));
    lives_indicator_ui->set_origin_alignment(sge::Alignment(sge::HotizontalAlignment::LEFT, sge::VerticalAlignment::TOP));
}

void PlayerUI::on_update() {
    if (!score_animation.is_done()) {
        int animated_score_val =  std::ceil(score_animation.step(env()->delta_time()));
        score_text->set_string(get_string_with_leading_zeros(animated_score_val, NG_PLAYER_SCORE_NUMBER_OF_DIGITS));
        represented_score_val = animated_score_val;
    }

}

void PlayerUI::on_destruction() {
}

void PlayerUI::on_scene_resume() {
    score_animation.stop();
    score_text->set_string(get_string_with_leading_zeros(player_persistent_data->score.value(), NG_PLAYER_SCORE_NUMBER_OF_DIGITS));
}

void PlayerUI::on_scene_destruction() {
    player_persistent_data->score.unsubscribe(score_changed_ev_handler);
}

std::string PlayerUI::get_string_with_leading_zeros(int amount, int number_of_digits) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(number_of_digits) << amount;
    return ss.str();
}
