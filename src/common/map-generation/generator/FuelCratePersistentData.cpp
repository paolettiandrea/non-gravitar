#include "FuelCratePersistentData.hpp"

void FuelCratePersistentData::apply_effect_on_player(Player *player_logic) {
    auto *data = player_logic->get_persistent_data();
    auto new_val = std::min(data->fuel_amount.value() + 50, data->fuel_max.value());
    data->fuel_amount.set(new_val);
}
