#ifndef NON_GRAVITAR_BREAKABLE_HPP
#define NON_GRAVITAR_BREAKABLE_HPP


#include <vector>
#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/VertArray.hpp>
#include "FragmentInfo.hpp"

class Breakable : public sge::Logic {
public:
    Breakable(float impact_velocity, bool child_dependent);

    std::string get_logic_id() override;

    void pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) override;

    void on_update() override;

    // Event used for external handling
    utils::event::Event break_handler_event;

private:
    float max_impact_velocity;
    bool m_child_dependent;


    void collect_fragment_info(std::vector<FragmentInfo>& container);
    void break_pulse(std::vector<FragmentInfo>& container);

    std::vector<FragmentInfo> collected_fragment_info;
};


#endif //NON_GRAVITAR_BREAKABLE_HPP
