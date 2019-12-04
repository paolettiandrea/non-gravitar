#ifndef NON_GRAVITAR_BULLET_HPP
#define NON_GRAVITAR_BULLET_HPP


#include <SGE/logic/Logic.hpp>

class Bullet : public sge::Logic {
public:
    Bullet (utils::Handle<sge::cmp::Rigidbody> ignore_body);
    std::string get_logic_id() override;

    void on_start() override;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

    void pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) override;

private:
    utils::Handle<sge::cmp::Rigidbody> m_ignore_body;


};


#endif //NON_GRAVITAR_BULLET_HPP
