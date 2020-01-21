#ifndef NON_GRAVITAR_PAUSELAUNCHER_HPP
#define NON_GRAVITAR_PAUSELAUNCHER_HPP


#include <SGE/logic/Logic.hpp>
#include "CONTROLS.hpp"

class PauseLauncher : public sge::Logic {
public:
    std::string get_logic_id() override;

    void on_update() override;
};


#endif //NON_GRAVITAR_PAUSELAUNCHER_HPP
