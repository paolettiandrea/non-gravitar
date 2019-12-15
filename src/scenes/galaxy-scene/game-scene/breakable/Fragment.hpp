#ifndef NON_GRAVITAR_FRAGMENT_HPP
#define NON_GRAVITAR_FRAGMENT_HPP

#include <SGE/logic/Logic.hpp>
#include "FragmentInfo.hpp"

class Fragment : public sge::Logic {
public:
    Fragment(const FragmentInfo& info, unsigned int event_id);

    void on_start() override;

    void pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) override;

    std::string get_logic_id() override;

    FragmentInfo get_info();

private:
    FragmentInfo info;

    unsigned int break_event_id;
};


#endif //NON_GRAVITAR_FRAGMENT_HPP
