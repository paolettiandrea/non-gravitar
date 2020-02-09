#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include <iomanip>
#include "ScoreIndicator.hpp"

ScoreIndicator::ScoreIndicator(ScoreIndicatorCD cd)
: score_animation(new LinearInterpolator(), 0, 0, NG_PLAYER_UI_SCORE_ANIMATION_DURATION) {
    this->cd = cd;
}

std::string ScoreIndicator::get_logic_id() {
    return std::string("ScoreIndicator");
}

void ScoreIndicator::on_update() {
    if (!score_animation.is_done()) {
        int animated_score_val =  std::ceil(score_animation.step(env()->delta_time()));
        score_text->set_string(get_string_with_leading_zeros(animated_score_val, NG_PLAYER_SCORE_NUMBER_OF_DIGITS));
        represented_score_val = animated_score_val;
    }
}

void ScoreIndicator::on_start() {
    auto score_ui = gameobject()->add_component<sge::cmp::UI>("UI");
    auto score_header_content = new sge::UIText(cd.header_string, NG_PLAYER_UI_SCORE_FONT_ID, NG_PLAYER_UI_SCORE_HEADER_CHAR_SIZE);
    score_header_content->set_offset(cd.offset);
    score_ui->set_content(score_header_content);
    score_ui->set_anchor_alignment(cd.anchor_alignment);
    score_ui->set_origin_alignment(cd.origin_alignment);

    auto score_text_go = scene()->spawn_gameobject("Score Text");
    score_text_go->transform()->set_parent(gameobject()->transform());
    auto score_text_ui = score_text_go->add_component<sge::cmp::UI>("UI");
    score_text_ui->set_anchor_alignment(cd.anchor_alignment);
    score_text_ui->set_origin_alignment(cd.origin_alignment);
    score_text = new sge::UIText(get_string_with_leading_zeros(cd.val->value(), NG_PLAYER_SCORE_NUMBER_OF_DIGITS), NG_PLAYER_UI_SCORE_FONT_ID, NG_PLAYER_UI_SCORE_AMOUNT_CHAR_SIZE);
    score_text_ui->set_content(score_text);
    score_text->set_offset(cd.offset + sf::Vector2f(0, - NG_PLAYER_UI_SCORE_HEADER_CHAR_SIZE - NG_PLAYER_UI_SCORE_SPACING));

    score_changed_ev_handler = [&]() {
        score_animation.set_from_val(represented_score_val);
        score_animation.set_to_val(cd.val->value());
        score_animation.start();
    };
    cd.val->subscribe(score_changed_ev_handler);
}

std::string ScoreIndicator::get_string_with_leading_zeros(int amount, int number_of_digits) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(number_of_digits) << amount;
    return ss.str();
}

void ScoreIndicator::on_scene_destruction() {
    cd.val->unsubscribe(score_changed_ev_handler);
}


