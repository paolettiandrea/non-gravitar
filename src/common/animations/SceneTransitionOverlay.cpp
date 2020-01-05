#include "SceneTransitionOverlay.hpp"
#include "COLORS.hpp"

SceneTransitionOverlay::SceneTransitionOverlay(Interpolator *m_interpolator, float duration)
    : radius_animation(m_interpolator, 0, 1, duration) {}


void SceneTransitionOverlay::on_start() {
    ui = gameobject()->add_component<sge::cmp::UI>("UI");
    ui->set_anchor_alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::CENTER);
    ui->set_origin_alignment(sge::HotizontalAlignment::MIDDLE, sge::VerticalAlignment::CENTER);
    ui_content = new SceneTransitionUIContent();
    ui->set_content(ui_content);
    ui_content->set_circle_color(PLAYER_PALETTE.primary);
}



void SceneTransitionOverlay::on_update() {
    if (radius_animation.is_active()) {
        auto new_radius = radius_animation.step(env()->delta_time());
        ui_content->set_circle_radius(new_radius);

        if (radius_animation.is_done()) {
            if (post_animation_ev_handler) radius_animation.on_animation_ended.removeHandler(*post_animation_ev_handler);
            post_animation_ev_handler = nullptr;
        }
    }
}

std::string SceneTransitionOverlay::get_logic_id() {
    return std::string("SceneTransitionOverlay");
}

void SceneTransitionOverlay::expand(utils::event::EventHandler* post_expand_callback) {
    auto radius = get_max_window_radius();
    if (radius_animation.get_val()!=radius) {
        radius_animation.set_from_val(radius_animation.get_val());
        radius_animation.set_to_val(radius);
        radius_animation.on_animation_ended.clearSubscribers();
        radius_animation.on_animation_ended += *post_expand_callback;
        post_animation_ev_handler = post_expand_callback;
        radius_animation.start();
    }
}

void SceneTransitionOverlay::collapse() {
    auto max_radius = get_max_window_radius();
    if (radius_animation.get_val()!=0) {
        ui_content->set_circle_radius(max_radius);
        radius_animation.set_from_val(max_radius);
        radius_animation.set_to_val(0);
        radius_animation.start();
    }
}

float SceneTransitionOverlay::get_max_window_radius() {
    auto x = env()->get_window_size().x/2.0;
    auto y = env()->get_window_size().y/2.0;
    return std::sqrt(x*x + y*y)*1.2;
}


