#include <iomanip>
#include <iostream>

#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include "PlayerUI.hpp"
#include "ScoreIndicator.hpp"

std::string PlayerUI::get_logic_id() {
    return std::string("PlayerUI");
}

PlayerUI::PlayerUI(PlayerPersistentData *player_persistent_data) {
    this->player_persistent_data = player_persistent_data;
}

void PlayerUI::on_start() {

    lives_changed_ev_handler = [&](){
        lives_indicator_content->set_lives(player_persistent_data->lives.value());
    };
    player_persistent_data->lives.subscribe(lives_changed_ev_handler);


    ScoreIndicatorCD score_cd;
    score_cd.origin_alignment = sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP);
    score_cd.anchor_alignment = sge::Alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::TOP);
    score_cd.header_string = "SCORE";
    score_cd.val = &player_persistent_data->score;
    score_cd.offset = sf::Vector2f(0, -NG_PLAYER_UI_VERTICAL_PADDING);
    ScoreIndicator *score_indicator = new ScoreIndicator(score_cd);
    auto score_go = scene()->spawn_gameobject("Score Indicator");
    score_go->transform()->set_parent(gameobject()->transform());
    score_go->logichub()->attach_logic(score_indicator);

    ScoreIndicatorCD cd;
    cd.origin_alignment = sge::Alignment(sge::HotizontalAlignment::RIGHT, sge::VerticalAlignment::TOP);
    cd.anchor_alignment = sge::Alignment(sge::HotizontalAlignment::RIGHT, sge::VerticalAlignment::TOP);
    cd.header_string = "BONUS";
    cd.val = &player_persistent_data->bonus_score;
    cd.offset = sf::Vector2f(NG_PLAYER_UI_HORIZONTAL_PADDING, -NG_PLAYER_UI_VERTICAL_PADDING);
    ScoreIndicator *bonus_score_indicator = new ScoreIndicator(cd);
    auto bonus_score_go = scene()->spawn_gameobject("Bonus Score Indicator");
    bonus_score_go->logichub()->attach_logic(bonus_score_indicator);



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
    lives_indicator_content = new PlayerLivesIndicator(player_persistent_data->lives.value());
    lives_indicator_content->set_offset(sf::Vector2f(-NG_PLAYER_UI_HORIZONTAL_PADDING, -NG_PLAYER_UI_VERTICAL_PADDING - NG_PLAYER_UI_SCORE_HEADER_CHAR_SIZE - NG_PLAYER_UI_SCORE_SPACING));
    lives_indicator_ui->set_content(lives_indicator_content);
    lives_indicator_ui->set_anchor_alignment(sge::Alignment(sge::HotizontalAlignment::LEFT, sge::VerticalAlignment::TOP));
    lives_indicator_ui->set_origin_alignment(sge::Alignment(sge::HotizontalAlignment::LEFT, sge::VerticalAlignment::TOP));


    // FUEL BAR
    auto fuel_bar_go = scene()->spawn_gameobject("Fuel Bar UI");
    fuel_bar_go->transform()->set_parent(gameobject()->transform());
    auto fuel_bar_ui = fuel_bar_go->add_component<sge::cmp::UI>("UI");
    fuel_bar_ui->set_anchor_alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::BOTTOM);
    fuel_bar_ui->set_origin_alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::BOTTOM);

    fuel_bar = new sge::UIBar(player_persistent_data->fuel_max.value()*NG_PLAYER_UI_FUEL_BAR_WIDTH_MULTIPLIER, 20);
    fuel_bar->set_offset(sf::Vector2f(0, 20));
    fuel_bar_ui->set_content(fuel_bar);

    fuel_changed_ev_handler = [&]() {
        fuel_bar->set_bar(player_persistent_data->fuel_amount.value() / player_persistent_data->fuel_max.value());
    };
    player_persistent_data->fuel_amount.subscribe(fuel_changed_ev_handler);

    max_fuel_changed_ev_handler = [&](){
        fuel_bar->set_size(player_persistent_data->fuel_max.value() * NG_PLAYER_UI_FUEL_BAR_WIDTH_MULTIPLIER,
                           fuel_bar->get_height());
    };
    player_persistent_data->fuel_max.subscribe(max_fuel_changed_ev_handler);



    // STAMINA BAR
    auto stamina_bar_go = scene()->spawn_gameobject("Fuel Bar UI");
    stamina_bar_go->transform()->set_parent(gameobject()->transform());
    auto stamina_bar_ui = stamina_bar_go->add_component<sge::cmp::UI>("UI");
    stamina_bar_ui->set_anchor_alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::BOTTOM);
    stamina_bar_ui->set_origin_alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::BOTTOM);

    stamina_bar = new sge::UIBar(player_persistent_data->stamina_max.value()*NG_PLAYER_UI_FUEL_BAR_WIDTH_MULTIPLIER, 20);
    stamina_bar->set_offset(sf::Vector2f(0, 50));
    stamina_bar_ui->set_content(stamina_bar);

    stamina_changed_ev_handler = [&]() {
        stamina_bar->set_bar(player_persistent_data->stamina_amount.value() / player_persistent_data->stamina_max.value());
    };
    player_persistent_data->stamina_amount.subscribe(stamina_changed_ev_handler);

    max_stamina_changed_ev_handler = [&](){
        stamina_bar->set_size(player_persistent_data->stamina_max.value() * NG_PLAYER_UI_FUEL_BAR_WIDTH_MULTIPLIER,
                           stamina_bar->get_height());
    };
    player_persistent_data->stamina_max.subscribe(max_fuel_changed_ev_handler);

    stamina_changed_ev_handler();
    fuel_changed_ev_handler();
}

void PlayerUI::on_destruction() {
}

void PlayerUI::on_scene_resume() {
    score_text->set_string(get_string_with_leading_zeros(player_persistent_data->score.value(), NG_PLAYER_SCORE_NUMBER_OF_DIGITS));
}

void PlayerUI::on_scene_destruction() {
    player_persistent_data->lives.unsubscribe(lives_changed_ev_handler);
    player_persistent_data->fuel_amount.unsubscribe(fuel_changed_ev_handler);
    player_persistent_data->fuel_max.unsubscribe(max_fuel_changed_ev_handler);
    player_persistent_data->stamina_amount.unsubscribe(stamina_changed_ev_handler);
    player_persistent_data->stamina_max.unsubscribe(max_stamina_changed_ev_handler);
}

std::string PlayerUI::get_string_with_leading_zeros(int amount, int number_of_digits) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(number_of_digits) << amount;
    return ss.str();
}
