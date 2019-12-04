#ifndef NON_GRAVITAR_ENEMYPART_HPP
#define NON_GRAVITAR_ENEMYPART_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/graphics/VertArray.hpp>
#include "SGE/components/physics/Collider.hpp"

class EnemyPart : public sge::Logic {
public:
    EnemyPart(const std::string& mesh_file_path, const std::string& collider_file_path);

    void on_start() override;

    utils::Handle<sge::cmp::Collider> get_collider();

    utils::Handle<sge::cmp::VertArray> get_vertarray();

private:
    std::string mesh_file_path;
    std::string collider_file_path;

    utils::Handle<sge::cmp::Collider> m_collider;
    utils::Handle<sge::cmp::VertArray> m_vertarray;
};


#endif //NON_GRAVITAR_ENEMYPART_HPP
