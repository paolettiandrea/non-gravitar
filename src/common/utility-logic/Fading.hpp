#ifndef NON_GRAVITAR_FADING_HPP
#define NON_GRAVITAR_FADING_HPP

#include <SGE/logic/Logic.hpp>
#include <SGE/utils/animation/Animation.hpp>

#define NG_FADING_ANIMATION_DURATION 0.3

// Make the Gameobject is attached to fade away and be doomed when invisible
// For now the object just assumes the vertarrays to be starting at alpha=1, this can be extended if necessary
class Fading : public sge::Logic {
public:
    explicit Fading();
    void on_start() override;

    void on_update() override;

    std::string get_logic_id() override;

private:
    sge::Animation fade_animation;

    void set_vert_array_alpha_recursive(utils::Handle<sge::GameObject> target_go, float alpha);
};


#endif //NON_GRAVITAR_FADING_HPP
