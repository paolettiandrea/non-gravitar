#include "ExtraLifeCratePersistentData.hpp"

std::string ExtraLifeCratePersistentData::get_content_smesh_path() {
    return std::string("./res/models/player/player_ship__body.smesh");
}

void ExtraLifeCratePersistentData::apply_effect_on_player(Player *player_logic) {
    player_logic->get_persistent_data()->lives.set(player_logic->get_persistent_data()->lives.value() + 1);
}

float ExtraLifeCratePersistentData::get_content_logo_scale() {
    return 0.7;
}
