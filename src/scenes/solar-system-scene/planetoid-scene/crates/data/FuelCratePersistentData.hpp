#ifndef NON_GRAVITAR_FUELCRATEPERSISTENTDATA_HPP
#define NON_GRAVITAR_FUELCRATEPERSISTENTDATA_HPP


#include "CratePersistentData.hpp"

class FuelCratePersistentData : public CratePersistentData {
public:
    void apply_effect_on_player(Player *player_logic) override;

    sf::Color get_overlay_color() override;
};


#endif //NON_GRAVITAR_FUELCRATEPERSISTENTDATA_HPP
