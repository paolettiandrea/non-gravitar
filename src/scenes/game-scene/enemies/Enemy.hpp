#ifndef NON_GRAVITAR_ENEMY_HPP
#define NON_GRAVITAR_ENEMY_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/physics/Rigidbody.hpp>

class Enemy : public sge::Logic {
public:
    void on_start() override;

protected:
    utils::Handle<sge::cmp::Rigidbody> m_rigidbody;
};


#endif //NON_GRAVITAR_ENEMY_HPP
