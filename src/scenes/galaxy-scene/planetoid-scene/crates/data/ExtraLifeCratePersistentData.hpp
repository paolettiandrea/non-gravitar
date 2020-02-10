#ifndef NON_GRAVITAR_EXTRALIFECRATEPERSISTENTDATA_HPP
#define NON_GRAVITAR_EXTRALIFECRATEPERSISTENTDATA_HPP


#include "ImprovementCrate.hpp"

class ExtraLifeCratePersistentData : public ImprovementCrate {
    std::string get_content_smesh_path() override;

    void apply_effect_on_player(Player *player_logic) override;

public:
    float get_content_logo_scale() override;
};


#endif //NON_GRAVITAR_EXTRALIFECRATEPERSISTENTDATA_HPP
