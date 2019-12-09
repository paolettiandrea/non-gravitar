#ifndef NON_GRAVITAR_CANNON_HPP
#define NON_GRAVITAR_CANNON_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/physics/Rigidbody.hpp>
#include <Bullet.hpp>


class Cannon : public sge::Logic {
public:
    explicit Cannon (float shooting_velocity, Rigidbody_H shooter_rigidbody);

    std::string get_logic_id() override;

    void shoot(Bullet* bullet_logic);


private:
    float m_shooting_vel;
    Rigidbody_H m_shooter_rigidbody;
};


#endif //NON_GRAVITAR_CANNON_HPP
