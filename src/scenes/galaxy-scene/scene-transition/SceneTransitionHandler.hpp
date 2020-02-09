#ifndef NON_GRAVITAR_SCENETRANSITIONHANDLER_HPP
#define NON_GRAVITAR_SCENETRANSITIONHANDLER_HPP


#include <SGE/logic/Logic.hpp>
#include <Player.hpp>
#include <PlanetoidPersistentData.hpp>
#include "MiniaturePlanetoid.hpp"
#include <SceneTransitionOverlay.hpp>


#define NG_GALAXY_SCENE_TRANSITION_DRIFTING_VELOCITY 0.5

class SceneTransitionHandler : public sge::Logic {
public:
    explicit SceneTransitionHandler(SceneTransitionHandler *parent_transition_handler);
    void on_start() override;

    virtual void pop_scene();

protected:
    void start_transition_animation(utils::event::EventHandler* post_animation_callback);


    SceneTransitionOverlay *scene_transition_overlay_l;
private:
    SceneTransitionHandler* parent_transition_handler;

    utils::event::EventHandler pop_callback;



};


#endif //NON_GRAVITAR_SCENETRANSITIONHANDLER_HPP
