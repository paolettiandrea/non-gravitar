#ifndef NON_GRAVITAR_MAXSTAMINACRATEPERSISTENTDATA_HPP
#define NON_GRAVITAR_MAXSTAMINACRATEPERSISTENTDATA_HPP

#include "ImprovementCrate.hpp"

class MaxStaminaCratePersistentData : public ImprovementCrate {
public:
    void apply_effect_on_player(Player *player_logic) override {     std::cout << "TODO increase fuelmax\n"; }
};

#endif //NON_GRAVITAR_MAXSTAMINACRATEPERSISTENTDATA_HPP
