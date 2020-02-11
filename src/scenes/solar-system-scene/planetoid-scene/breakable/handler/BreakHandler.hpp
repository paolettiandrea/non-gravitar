#ifndef NON_GRAVITAR_BREAKHANDLER_HPP
#define NON_GRAVITAR_BREAKHANDLER_HPP


#include <SGE/logic/Logic.hpp>
#include "FragmentInfo.hpp"


#define NG_BREAK_ENERGY_ABSORPTION_FACTOR 0.8

struct ExplosionInfo {
    sge::Vec2<float> explosion_local_position = sge::Vec2<float>(0,0);
    float explosion_force = 0.0;
    float explosion_radius = 1.0;
};

class BreakHandler : public sge::Logic {
public:
    explicit BreakHandler(const ExplosionInfo& explosion_info, bool is_child_dependent = true, bool fade_on_break = false, const std::string& fragment_collision_layer = "Default");
    explicit BreakHandler(bool is_child_dependent = true, bool fade_on_break = false, const std::string& fragment_collision_layer = "Default");

    std::string get_logic_id() override;

    bool is_child_dependent() const;

    void break_pulse(b2Vec2 linear_vel_at_break, float trigger_val);

    void on_update() override;

    sge::Vec2<float> get_explosion_world_pos();

private:
    static unsigned int break_event_counter;
    bool m_child_dependent_flag;
    bool m_fade_on_break_flag;
    std::string fragment_collision_layer;
    b2Vec2 linear_vel_at_break;
    float trigger_val_at_break;
    ExplosionInfo explosion_info;
    sge::Vec2<float> explosion_pos_at_break;


    std::vector<std::vector<FragmentInfo>> collected_fragment_info;
    unsigned int break_event_id = 0;

    static void recursive_info_collection(std::vector<std::vector<FragmentInfo>>& container, GameObject_H target);

};




#endif //NON_GRAVITAR_BREAKHANDLER_HPP
