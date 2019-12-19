#ifndef NON_GRAVITAR_GALAXYSCENE_ENTRYLOGIC_HPP
#define NON_GRAVITAR_GALAXYSCENE_ENTRYLOGIC_HPP


#include <SGE/logic/Logic.hpp>


class GalaxyScene_EntryLogic : public sge::Logic {
public:
    void on_start() override;

    std::string get_logic_id() override;

    PlayerPersistentData player_persistent_data;
};


#endif //NON_GRAVITAR_GALAXYSCENE_ENTRYLOGIC_HPP
