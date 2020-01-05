#ifndef NON_GRAVITAR_SCENETRANSITIONOVERLAY_HPP
#define NON_GRAVITAR_SCENETRANSITIONOVERLAY_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/utils/interpolation/Interpolator.hpp>
#include <SGE/utils/animation/Animation.hpp>
#include <SGE/components/graphics/VertArray.hpp>
#include <SGE/components/graphics/ui/UI.hpp>
#include "SceneTransitionUiContent.hpp"

class SceneTransitionOverlay : public sge::Logic {

public:
    SceneTransitionOverlay(Interpolator *m_interpolator, float duration);

    std::string get_logic_id() override;

    utils::event::Event& get_transition_ended_event() { return radius_animation.on_animation_ended; }

    void on_start() override;
    void on_update() override;

    void expand(utils::event::EventHandler* post_expand_callback = nullptr);
    void collapse();

    sge::Animation& get_radius_animation() { return radius_animation; }

private:
    sge::Animation radius_animation;
    UI_H ui;
    SceneTransitionUIContent* ui_content;

    utils::event::EventHandler* post_animation_ev_handler;

    float get_max_window_radius();
};


#endif //NON_GRAVITAR_SCENETRANSITIONOVERLAY_HPP
