#include "Fragment.hpp"
#include "FragmentedLayerGenerator.hpp"

string FragmentedLayerGenerator::get_logic_id() {
    return std::string("FragmentedLayerGenerator");
}

void FragmentedLayerGenerator::collect_fragment_info(std::vector<FragmentInfo> &container) {
    for (auto child : gameobject()->transform()->get_children()) {
        auto fragment_l = child->gameobject()->logichub()->get_logic_by_id<Fragment>("Fragment");
        if (fragment_l) {
            auto info = fragment_l->get_info();

            auto vert_array = fragment_l->gameobject()->get_component<sge::cmp::VertArray>("VertArray");

            if (!vert_array.is_null() && vert_array->get_vert_array().getVertexCount() == 3) {
                for (int i = 0; i < vert_array->get_vert_array().getVertexCount()/3; ++i) {
                    container.emplace_back(vert_array, i*3, m_max_triangles);
                }
            } else {
                LOG_ERROR << "Breakable logic uses the VertArray data to spawn the fragments,"
                             " there's no such component on this Gameobject";
                exit(1);
            }
        }
        else {
            LOG_ERROR << "Couldn't find Fragment logic in an object expected to have it";
            exit(1);
        }
    }
}

FragmentedLayerGenerator::FragmentedLayerGenerator(unsigned int max_triangles_per_piece) : BreakGenerator(
        max_triangles_per_piece) {}
