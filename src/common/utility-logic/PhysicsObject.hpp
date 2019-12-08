#ifndef NON_GRAVITAR_PHYSICSOBJECT_HPP
#define NON_GRAVITAR_PHYSICSOBJECT_HPP

#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/VertArray.hpp>
#include <SGE/components/physics/Collider.hpp>

class PhysicsObject_ConstructionData{
public:
    explicit PhysicsObject_ConstructionData(const std::string& truncated_load_path) {
        mesh_path = truncated_load_path + ".smesh";
        collider_path = truncated_load_path + "_collider.spath";
    }
    explicit PhysicsObject_ConstructionData(const std::string& truncated_load_path, const PhysicsMaterial& physics_material1) {
        mesh_path = truncated_load_path + ".smesh";
        collider_path = truncated_load_path + "_collider.spath";
        physics_material = physics_material1;
    }

    [[nodiscard]] const std::string &get_mesh_path() const {
        return mesh_path;
    }

    [[nodiscard]] const std::string &get_collider_path() const {
        return collider_path;
    }

    const PhysicsMaterial &get_physics_material() const {
        return physics_material;
    }

private:
    std::string mesh_path;
    std::string collider_path;
    PhysicsMaterial physics_material;
};

class BreakableObject_ConstructionData : public PhysicsObject_ConstructionData {
public:
    BreakableObject_ConstructionData(const std::string &truncated_load_path, unsigned int max_stuck_pieces_on_break);
    BreakableObject_ConstructionData(const std::string &truncated_load_path, const PhysicsMaterial& physics_material1, unsigned int max_stuck_pieces_on_break);

    unsigned int get_max_stuck_pieces_on_break() const;

private:
    unsigned int max_stuck_pieces_on_break;


};

// Logic that loads on start a smesh file for the VertArray and a spath file for the Collider
class PhysicsObject : public sge::Logic {
public:
    explicit PhysicsObject(const PhysicsObject_ConstructionData& cd);

    void on_start() override;

    utils::Handle<sge::cmp::VertArray> vertarray();
    utils::Handle<sge::cmp::Collider> collider();

private:
    PhysicsObject_ConstructionData physics_construction_data;

    utils::Handle<sge::cmp::Collider> m_collider;
    utils::Handle<sge::cmp::VertArray> m_vertarray;
};


#endif //NON_GRAVITAR_PHYSICSOBJECT_HPP
