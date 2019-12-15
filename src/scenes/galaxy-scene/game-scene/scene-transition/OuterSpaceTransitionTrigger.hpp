#ifndef NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP
#define NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP


#include <SGE/logic/Logic.hpp>

#define NG_TRIGGER_COLLIDER_THICKNESS 20


class OuterSpaceTransitionTrigger : public sge::Logic {
public:
    explicit OuterSpaceTransitionTrigger(float radius);

    void on_start() override;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

    std::string get_logic_id() override;

private:
    float radius;
};


#endif //NON_GRAVITAR_OUTERSPACETRANSITIONTRIGGER_HPP
