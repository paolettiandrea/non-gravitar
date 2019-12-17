#ifndef NON_GRAVITAR_PLANETOIDSCENETRANSITIONTRIGGER_HPP
#define NON_GRAVITAR_PLANETOIDSCENETRANSITIONTRIGGER_HPP


#include <SGE/logic/Logic.hpp>
#include "SceneTransitionHandler.hpp"

class PlanetoidSceneTransitionTrigger : public sge::Logic {
public:
    PlanetoidSceneTransitionTrigger(SceneTransitionHandler *transition_handler);
    std::string get_logic_id() override;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

private:
    SceneTransitionHandler* handler;
};


#endif //NON_GRAVITAR_PLANETOIDSCENETRANSITIONTRIGGER_HPP
