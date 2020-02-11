#ifndef NON_GRAVITAR_MAXSTAMINACRATEPERSISTENTDATA_HPP
#define NON_GRAVITAR_MAXSTAMINACRATEPERSISTENTDATA_HPP

#include "ImprovementCrate.hpp"

class MaxStaminaCratePersistentData : public ImprovementCrate {
public:
    void apply_effect_on_player(Player *player_logic) override {
        player_logic->get_persistent_data()->stamina_max.set(player_logic->get_persistent_data()->stamina_max.value() + 20);
        player_logic->get_persistent_data()->stamina_amount.set(player_logic->get_persistent_data()->stamina_max.value());
    }
};

#endif //NON_GRAVITAR_MAXSTAMINACRATEPERSISTENTDATA_HPP
