#ifndef NON_GRAVITAR_PLAYERUI_HPP
#define NON_GRAVITAR_PLAYERUI_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/ui/UI.hpp>
#include <player/PlayerPersistentData.hpp>
#include <SGE/utils/animation/Animation.hpp>
#include <SGE/components/graphics/ui/blocks/UIText.hpp>
#include <SGE/components/graphics/ui/blocks/UIBar.hpp>
#include "PlayerLivesIndicator.hpp"


#define NG_PLAYER_UI_HORIZONTAL_PADDING         20
#define NG_PLAYER_UI_VERTICAL_PADDING           20

#define NG_PLAYER_UI_FUEL_BAR_WIDTH_MULTIPLIER  3




class PlayerUI : public sge::Logic {
public:
    PlayerUI(PlayerPersistentData *player_persistent_data);

    void on_start() override;

    std::string get_logic_id() override;

    void on_destruction() override;

    void on_scene_destruction() override;

    void on_scene_resume() override;

private:
    PlayerPersistentData *player_persistent_data;
    sge::UIText* score_text;
    sge::UIBar* fuel_bar;
    sge::UIBar *stamina_bar;


    utils::event::EventHandler fuel_changed_ev_handler;
    utils::event::EventHandler max_fuel_changed_ev_handler;
    utils::event::EventHandler stamina_changed_ev_handler;
    utils::event::EventHandler max_stamina_changed_ev_handler;

    utils::event::EventHandler lives_changed_ev_handler;
    PlayerLivesIndicator* lives_indicator_content;

    static std::string get_string_with_leading_zeros(int amount, int number_of_digits);





};


#endif //NON_GRAVITAR_PLAYERUI_HPP
