#ifndef NON_GRAVITAR_COLLISIONTRIGGER_HPP
#define NON_GRAVITAR_COLLISIONTRIGGER_HPP

#include <SGE/logic/Logic.hpp>
#include <SGE/components/physics/Collider.hpp>

typedef std::function<void(const sge::CollisionInfo& collision_info)> CollisionCallback;

class CollisionTrigger : public sge::Logic {
public:
    explicit CollisionTrigger(const CollisionCallback& callback);
    std::string get_logic_id() override;

    void on_start() override;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

    Collider_H collider;

private:
    CollisionCallback callback;


};


#endif //NON_GRAVITAR_COLLISIONTRIGGER_HPP
