#ifndef NON_GRAVITAR_BREAKHANDLER_HPP
#define NON_GRAVITAR_BREAKHANDLER_HPP


#include <SGE/logic/Logic.hpp>
#include "FragmentInfo.hpp"

class BreakHandler : public sge::Logic {
public:
    explicit BreakHandler(bool is_child_dependent);

    std::string get_logic_id() override;

    bool is_child_dependent() const;

    void break_pulse();

    void on_update() override;

private:
    static unsigned int break_event_counter;
    bool m_child_dependent_flag;

    std::vector<std::vector<FragmentInfo>> collected_fragment_info;
    unsigned int break_event_id = 0;

    static void recursive_info_collection(std::vector<std::vector<FragmentInfo>>& container, utils::Handle<sge::GameObject> target);

};




#endif //NON_GRAVITAR_BREAKHANDLER_HPP
