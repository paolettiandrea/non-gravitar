#ifndef NON_GRAVITAR_SCOREINDICATOR_HPP
#define NON_GRAVITAR_SCOREINDICATOR_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/ui/UI.hpp>
#include <player/PlayerPersistentData.hpp>
#include <SGE/utils/animation/Animation.hpp>

#define NG_PLAYER_UI_SCORE_FONT_ID              "ARCADE_R"
#define NG_PLAYER_UI_SCORE_HEADER_CHAR_SIZE     20
#define NG_PLAYER_UI_SCORE_SPACING              5
#define NG_PLAYER_UI_SCORE_AMOUNT_CHAR_SIZE     20

#define NG_PLAYER_SCORE_NUMBER_OF_DIGITS        9

#define NG_PLAYER_UI_SCORE_ANIMATION_DURATION   0.5

struct ScoreIndicatorCD {
    std::string header_string;
    sge::Alignment anchor_alignment;
    sge::Alignment origin_alignment;
    sf::Vector2f offset;
    WatchedVal<int>* val;
};

class ScoreIndicator : public sge::Logic {
public:
    explicit ScoreIndicator(ScoreIndicatorCD cd);

    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

    void on_scene_destruction() override;

private:
    ScoreIndicatorCD cd;
    sge::Animation score_animation;
    sge::UIText* score_text;
    utils::event::EventHandler score_changed_ev_handler;
    int represented_score_val = 0;

    static std::string get_string_with_leading_zeros(int amount, int number_of_digits);
};


#endif //NON_GRAVITAR_SCOREINDICATOR_HPP
