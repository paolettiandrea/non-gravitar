#ifndef NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP
#define NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP


#include <SGE/logic/Logic.hpp>
#include <scaled-planetoid/MiniaturePlanetoid.hpp>

#define NG_TRIGGER_COLLIDER_THICKNESS 20


class OuterSpaceTransitionTrigger : public sge::Logic {
public:
    explicit OuterSpaceTransitionTrigger(float radius, MiniaturePlanetoid* miniature_planetoid);

    void on_start() override;

    std::string get_logic_id() override;

private:
    float radius;

    MiniaturePlanetoid *base_planetoid;
};


#endif //NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP