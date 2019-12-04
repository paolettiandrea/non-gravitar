#ifndef NON_GRAVITAR_CANNON_HPP
#define NON_GRAVITAR_CANNON_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/physics/Rigidbody.hpp>
#include <Bullet.hpp>


class Cannon : public sge::Logic {
public:
    explicit Cannon (float shooting_velocity, float shooting_frequency);

    std::string get_logic_id() override;

    void on_fixed_update() override;

    void shoot(Bullet* bullet_logic);


    void on_start() override;
private:

    float m_shooting_vel;
    float m_shooting_period;

    std::chrono::time_point<std::chrono::steady_clock> m_last_shot_time;

    int bullet_counter = 0;





};


#endif //NON_GRAVITAR_CANNON_HPP
