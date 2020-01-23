#ifndef NON_GRAVITAR_MAXFUELCRATEPERSISTENTDATA_HPP
#define NON_GRAVITAR_MAXFUELCRATEPERSISTENTDATA_HPP


#include "ImprovementCrate.hpp"

class MaxFuelCratePersistentData : public ImprovementCrate {
public:
    void apply_effect_on_player(Player *player_logic) override {     std::cout << "TODO increase fuelmax\n"; }
};


#endif //NON_GRAVITAR_MAXFUELCRATEPERSISTENTDATA_HPP
