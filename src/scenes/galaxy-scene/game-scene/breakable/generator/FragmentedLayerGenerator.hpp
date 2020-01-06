#ifndef NON_GRAVITAR_FRAGMENTEDLAYERGENERATOR_HPP
#define NON_GRAVITAR_FRAGMENTEDLAYERGENERATOR_HPP


#include "BreakGenerator.hpp"

class FragmentedLayerGenerator : public BreakGenerator {
public:
    FragmentedLayerGenerator(unsigned int max_triangles_per_piece);

    string get_logic_id() override;

    void collect_fragment_info(std::vector<FragmentInfo> &container) override;
};


#endif //NON_GRAVITAR_FRAGMENTEDLAYERGENERATOR_HPP
