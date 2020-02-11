#ifndef NON_GRAVITAR_BREAKGENERATOR_HPP
#define NON_GRAVITAR_BREAKGENERATOR_HPP


#include <SGE/logic/Logic.hpp>
#include "FragmentInfo.hpp"

class BreakGenerator : public sge::Logic {
public:
    explicit BreakGenerator(unsigned int max_triangles_per_piece);
    virtual void collect_fragment_info(std::vector<FragmentInfo>& container);

    std::string get_logic_id() override;

protected:
    unsigned int m_max_triangles;
};


#endif //NON_GRAVITAR_BREAKGENERATOR_HPP
