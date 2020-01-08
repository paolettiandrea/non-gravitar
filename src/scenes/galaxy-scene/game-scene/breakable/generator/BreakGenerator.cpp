#include <SGE/components/graphics/VertArray.hpp>
#include "BreakGenerator.hpp"

void BreakGenerator::collect_fragment_info(std::vector <FragmentInfo> &container) {
    auto vert_array = gameobject()->get_component<sge::cmp::VertArray>("VertArray");
    if (!vert_array.is_null() && vert_array->get_vert_array().getVertexCount() > 0) {
        if (vert_array->get_primitive_type() == sf::PrimitiveType::Triangles) {
            for (int i = 0; i < vert_array->get_vert_array().getVertexCount()/3; ++i) {
                container.emplace_back(vert_array, i*3, m_max_triangles);
            }
        } else {
            LOG_ERROR << "A VertArray with PrimitiveType==Triangles is needed";
            exit(1);
        }
    } else {
        LOG_ERROR << "Breakable logic uses the VertArray data to spawn the fragments,"
                     " there's no such component on this Gameobject";
        exit(1);
    }
}

std::string BreakGenerator::get_logic_id() {
    return std::string("BreakGenerator");
}

BreakGenerator::BreakGenerator(unsigned int max_triangles_per_piece) {
    m_max_triangles = max_triangles_per_piece;
}
