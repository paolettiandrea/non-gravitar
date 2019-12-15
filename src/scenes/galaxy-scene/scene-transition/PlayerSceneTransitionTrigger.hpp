#ifndef NON_GRAVITAR_PLAYERSCENETRANSITIONTRIGGER_HPP
#define NON_GRAVITAR_PLAYERSCENETRANSITIONTRIGGER_HPP


#include <SGE/logic/Logic.hpp>
#include "SceneTransitionHandler.hpp"

class PlayerSceneTransitionTrigger : public sge::Logic {
public:
    PlayerSceneTransitionTrigger(SceneTransitionHandler *transition_handler);
    std::string get_logic_id() override;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

private:
    SceneTransitionHandler* handler;
};


#endif //NON_GRAVITAR_PLAYERSCENETRANSITIONTRIGGER_HPP
