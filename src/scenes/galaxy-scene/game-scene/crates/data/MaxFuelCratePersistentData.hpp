#ifndef NON_GRAVITAR_MAXFUELCRATEPERSISTENTDATA_HPP
#define NON_GRAVITAR_MAXFUELCRATEPERSISTENTDATA_HPP


#include "ImprovementCrate.hpp"

class MaxFuelCratePersistentData : public ImprovementCrate {
public:
    void apply_effect_on_player(Player *player_logic) override {
        player_logic->get_persistent_data()->fuel_max.set(player_logic->get_persistent_data()->fuel_max.value() + 20);
        player_logic->get_persistent_data()->fuel_amount.set(player_logic->get_persistent_data()->fuel_max.value());
    }
};


#endif //NON_GRAVITAR_MAXFUELCRATEPERSISTENTDATA_HPP
