#include "Minimap.hpp"

std::string Minimap::get_logic_id() {
    return std::string("Minimap");
}

void Minimap::on_start() {
    auto ui = gameobject()->add_component<sge::cmp::UI>("UI");
    minimap_ui_content = new Minimap_UIContent(base_miniature);
    ui->set_content(minimap_ui_content);
    ui->set_anchor_alignment(sge::Alignment(sge::RIGHT, sge::BOTTOM));
    ui->set_origin_alignment(sge::Alignment(sge::RIGHT, sge::BOTTOM));

    minimap_ui_content->set_offset(sf::Vector2f(25, 25));
}

void Minimap::on_update() {
    Logic::on_update();

    counter += env()->delta_time();
    if (counter > NG_MINIMAP_REFRESH_PERIOD) {
        counter -= NG_MINIMAP_REFRESH_PERIOD;

        std::vector<MinimapTraced_I*> objects_to_trace;
        objects_to_trace.push_back(player);

        auto enemies_build_data = planetoid->get_planetoid_persistent_data()->map_gen_info.enemies_build_data;
        for (int i = 0; i < enemies_build_data.size(); ++i) {
            auto* data = enemies_build_data[i];
            if (!data->destroyed) {
                objects_to_trace.push_back(data);
            }
        }

        minimap_ui_content->refresh_pins(objects_to_trace);

        LOG_INFO << "PINS";
    }
}

Minimap::Minimap(MiniaturePlanetoid *base_miniature, Planetoid *planetoid, Player *player) : base_miniature(
        base_miniature), planetoid(planetoid), player(player) {}
