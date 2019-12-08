#include <SGE/components/graphics/VertArray.hpp>
#include "Fading.hpp"

void Fading::on_start() {
    fade_animation.start();
}

std::string Fading::get_logic_id() {
    return std::string("Fading");
}

Fading::Fading()  : fade_animation(new LinearInterpolator, 255, 0, NG_FADING_ANIMATION_DURATION) {

}

void Fading::set_vert_array_alpha_recursive(utils::Handle<sge::GameObject> target_go, float alpha) {
    auto vert_array = target_go->get_component<sge::cmp::VertArray>("VertArray");
    if (vert_array.is_valid()) {
        vert_array->set_alpha(alpha);
    }

    for (auto child : target_go->transform()->get_children()) {
        set_vert_array_alpha_recursive(child->gameobject(), alpha);
    }
}

void Fading::on_update() {
    auto alpha = fade_animation.step(env()->delta_time());
    set_vert_array_alpha_recursive(gameobject(), alpha);

    if (alpha<=0) { gameobject()->doom(); }
}

