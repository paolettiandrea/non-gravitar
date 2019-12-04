#ifndef NON_GRAVITAR_BREAKTRIGGER_HPP
#define NON_GRAVITAR_BREAKTRIGGER_HPP


#include <SGE/logic/Logic.hpp>

/*!
 * /brief Can trigger a break of the object is attached to based on the velocity of the impact on its Collider
 */
class BreakTrigger : public sge::Logic {
public:
    BreakTrigger(float trigger_impact_vel);
    std::string get_logic_id() override;

    void pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) override;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

private:
    float m_trigger_impact_vel;
};


#endif //NON_GRAVITAR_BREAKTRIGGER_HPP
