#ifndef NON_GRAVITAR_PLAYERENGINE_HPP
#define NON_GRAVITAR_PLAYERENGINE_HPP


#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/graphics/ui/blocks/UIBar.hpp>
#include "SGE/logic/Logic.hpp"
#include "SGE/components/graphics/VertArray.hpp"

class PlayerEngine : public sge::Logic {
public:
    explicit PlayerEngine(Rigidbody_H rigidbody);

    std::string get_logic_id() override;

    void on_fixed_update() override;

    void on_update() override;

    void on_start() override;

private:

    enum ThrustStatus {Increasing, Stabilizing, Stable,  Decreasing, Zero};

    Rigidbody_H controlled_rigidbody;
    VertArray_H engine_trail;

    const sf::Keyboard::Key thrust_key = sf::Keyboard::W;
    // The time in seconds needed to reach maximum thrust force
    const float THRUST_INCREASE_TIME = 0.07;
    const float THRUST_STABILIZATION_TIME = 0.15;
    // The time in seconds needed to decrease thrust force to 0
    const float THRUST_DECREASE_TIME = 0.07;

    const float BASE_ACCELERATION = 25;
    const float MAX_INITIAL_THRUST_FACTOR = 1.2;

    // While the lenght of the displayed trail is proportional to the actual acceleration, this can be use to tune the result
    const float TRAIL_LENGHT_MULTIPLIER = 0.12;

    // The amount of force that needs to be added to the thrust every fixedupdate in order to reach the initial thrust tarhet in the target time
    float INITIAL_THRUST_TARGET;
    float INITIAL_FORCE_DELTA;
    float STABILIZATION_FORCE_DELTA;
    float DECREASE_FORCE_DELTA;


    float last_thrust_amount = 0;


    ThrustStatus thrust_status = Zero;

    static constexpr float FUEL_MAX = 100;
    static constexpr float FUEL_EFFICIENCY_FACTOR = 600;

    float m_fuel_amount = FUEL_MAX;
    float m_last_displayed_fuel_amount = 0;
    sge::UIBar* fuel_bar;



    void update_engine_trail_lenght();
};


#endif //NON_GRAVITAR_PLAYERENGINE_HPP
