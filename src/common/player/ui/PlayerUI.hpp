#ifndef NON_GRAVITAR_PLAYERUI_HPP
#define NON_GRAVITAR_PLAYERUI_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/ui/UI.hpp>
#include <player/PlayerPersistentData.hpp>
#include <SGE/utils/animation/Animation.hpp>

#define NG_PLAYER_UI_VERTICAL_PADDING 20
#define NG_PLAYER_UI_HORIZONTAL_PADDING 20
#define NG_PLAYER_UI_SCORE_HEADER_CHAR_SIZE 20
#define NG_PLAYER_UI_SCORE_SPACING 5
#define NG_PLAYER_UI_SCORE_AMOUNT_CHAR_SIZE 20

#define NG_PLAYER_SCORE_NUMBER_OF_DIGITS 9

#define NG_PLAYER_UI_SCORE_ANIMATION_DURATION 0.5

#define NG_PLAYER_UI_SCORE_FONT_ID "ARCADE_R"


class PlayerUI : public sge::Logic {
public:
    PlayerUI(PlayerPersistentData *player_persistent_data);

    void on_start() override;

    std::string get_logic_id() override;

    void on_update() override;

    void on_destruction() override;

    void on_scene_destruction() override;

    void on_scene_resume() override;

private:
    PlayerPersistentData *player_persistent_data;
    sge::UIText* score_text;


    sge::Animation score_animation;
    utils::event::EventHandler score_changed_ev_handler;
    int represented_score_val = 0;

    static std::string get_string_with_leading_zeros(int amount, int number_of_digits);



};


#endif //NON_GRAVITAR_PLAYERUI_HPP