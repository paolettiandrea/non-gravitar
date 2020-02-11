#ifndef NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP
#define NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP


#include <SGE/logic/Logic.hpp>
#include <scaled-planetoid/MiniaturePlanetoid.hpp>
#include <scene-transition/PlanetoidTransitionHandler.hpp>


#define NG_TRIGGER_COLLIDER_THICKNESS 20


class OuterSpaceTransitionTrigger : public sge::Logic {
public:
    explicit OuterSpaceTransitionTrigger(float radius, PlanetoidTransitionHandler* planetoid_transition_handler);

    void on_start() override;

    std::string get_logic_id() override;

private:
    float radius;

    MiniaturePlanetoid *base_planetoid;
    PlanetoidTransitionHandler *planetoid_transition_handler;
};


#endif //NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP
