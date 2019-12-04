#ifndef NON_GRAVITAR_TRIGGER_HPP
#define NON_GRAVITAR_TRIGGER_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/physics/Collider.hpp>

class Trigger : public sge::Logic {
public:
    std::string get_logic_id() override;

    Trigger(const std::string& target_logic_id);

    utils::event::Event on_collision_begin_event;
    utils::event::Event on_collision_end_event;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

    void on_collision_end(sge::CollisionInfo &collision_info) override;


private:
    std::string m_target_logic_id;
};


#endif //NON_GRAVITAR_TRIGGER_HPP
