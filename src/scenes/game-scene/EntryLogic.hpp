#ifndef NON_GRAVITAR_ENTRYLOGIC_HPP
#define NON_GRAVITAR_ENTRYLOGIC_HPP

#include "SGE/logic/Logic.hpp"

#include "CameraControls.hpp"
#include "Player.hpp"

class EntryLogic : public sge::Logic {
public:
    std::string get_logic_id() override;

    void on_start() override;
};


#endif //NON_GRAVITAR_ENTRYLOGIC_HPP
