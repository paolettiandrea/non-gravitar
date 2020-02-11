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
    refresh_geometry();

    scene()->get_camera()->ratio_changed_event += [&](){
        refresh_geometry();
    };
}

void Minimap::on_update() {
    Logic::on_update();

    counter += env()->delta_time();
    if (counter > NG_MINIMAP_REFRESH_PERIOD) {
        counter -= NG_MINIMAP_REFRESH_PERIOD;
        refresh_geometry();
    }
}

Minimap::Minimap(MiniaturePlanetoid *base_miniature, Planetoid *planetoid, PlayerSpawnManager* player_spawn_manager) : base_miniature(
        base_miniature), planetoid(planetoid), player_spawn_manager(player_spawn_manager) {
    player_persistent_data = player_spawn_manager->get_player_logic()->get_persistent_data();
}

void Minimap::refresh_geometry() {
    std::vector<MinimapTraced_I*> objects_to_trace;
    auto enemies_build_data = planetoid->get_planetoid_persistent_data()->map_gen_info.enemies_persistent_data_vec;
    for (int i = 0; i < enemies_build_data.size(); ++i) {
        auto* data = enemies_build_data[i];
        if (!data->destroyed) {
            objects_to_trace.push_back(data);
        }
    }

    auto crates_build_data = planetoid->get_planetoid_persistent_data()->map_gen_info.crates_persistent_data_vec;

    for (int i = 0; i < crates_build_data.size(); ++i) {
        auto* data = crates_build_data[i];
        if (!data->destroyed) {
            objects_to_trace.push_back(data);
        }
    }

    minimap_ui_content->refresh_geometry(player_spawn_manager->get_player_logic(), objects_to_trace, *player_persistent_data);
}
