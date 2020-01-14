#ifndef NON_GRAVITAR_TRIGGER_HPP
#define NON_GRAVITAR_TRIGGER_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/physics/Collider.hpp>

template <class T>
class Trigger : public sge::Logic {
public:
    std::string get_logic_id() override {
        return std::string("Trigger");
    }

    explicit Trigger(const std::string& target_logic_id) {
        m_target_logic_id = target_logic_id;
    }

    utils::event::Event on_collision_begin_event;
    utils::event::Event on_collision_end_event;

    void on_collision_begin(sge::CollisionInfo &collision_info) override {
        if (collision_info.m_its_collider.is_valid()) {
            auto found_logic = collision_info.m_its_collider->get_rigidbody()->gameobject()->logichub()->get_logic_by_id<T>(m_target_logic_id);
            if (found_logic != nullptr) {
                on_collision_begin_event();
                triggering_logic = found_logic;
            }
        }
    }

    void on_collision_end(sge::CollisionInfo &collision_info) override {
        if (collision_info.m_its_collider.is_valid()) {
            auto found_logic = collision_info.m_its_collider->get_rigidbody()->gameobject()->logichub()->get_logic_by_id<T>(m_target_logic_id);
            if (found_logic != nullptr) {
                on_collision_end_event();
                if (triggering_logic == found_logic) triggering_logic = nullptr;
            }
        }
    }

    T* get_triggering_logic() { return triggering_logic; }


private:
    std::string m_target_logic_id;
    T* triggering_logic;
};


#endif //NON_GRAVITAR_TRIGGER_HPP
