#ifndef NON_GRAVITAR_MINIMAP_HPP
#define NON_GRAVITAR_MINIMAP_HPP

#include <SGE/logic/Logic.hpp>
#include "Minimap_UIContent.hpp"
#include <SGE/components/graphics/ui/UI.hpp>
#include <player/Player.hpp>


#define NG_MINIMAP_REFRESH_PERIOD 0.25


class Minimap : public sge::Logic {
public:
    Minimap(MiniaturePlanetoid *base_miniature, Planetoid *planetoid, Player *player);

    std::string get_logic_id() override;

    void on_start() override;

    void on_update() override;

private:
    MiniaturePlanetoid* base_miniature;
    Planetoid* planetoid;
    Player *player;

    Minimap_UIContent* minimap_ui_content;

    float counter = 0;

    void refresh_geometry();
};

#endif //NON_GRAVITAR_MINIMAP_HPP
