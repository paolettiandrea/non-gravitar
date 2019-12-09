#ifndef NON_GRAVITAR_PLANETOID_HPP
#define NON_GRAVITAR_PLANETOID_HPP

#include <SGE/components/graphics/VertArray.hpp>
#include "SGE/components/physics/Rigidbody.hpp"
#include "SGE/components/physics/Collider.hpp"
#include "SGE/logic/Logic.hpp"
#include "PlanetoidData.hpp"

class Planetoid : public sge::Logic {
public:
    explicit Planetoid(const PlanetoidData& planetoid_data) { this->planetoid_data = &planetoid_data; }
    std::string get_logic_id() override;

    void on_start() override;

private:
    const PlanetoidData* planetoid_data;

    static void assemble_vert_array(VertArray_H recipient, const MarchingMap& marching_map);

};


#endif //NON_GRAVITAR_PLANETOID_HPP
