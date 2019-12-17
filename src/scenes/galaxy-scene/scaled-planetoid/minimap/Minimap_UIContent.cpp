#include <player/Player.hpp>
#include "Minimap_UIContent.hpp"

Minimap_UIContent::Minimap_UIContent(MiniaturePlanetoid *original) {
    base_miniature = original;
    auto palette = original->get_planetoid_persistent_data()->map_gen_info.palette;

    Planetoid::assemble_vert_array(main_fill_vert_array, *original->get_scaled_marching_map(), palette.primary);
    Planetoid::assemble_vert_array(main_fill_vert_array, *original->get_scaled_secondary_marching_map(), palette.dark);

    Planetoid::assemble_vert_array(background_vert_array, *original->get_scaled_fog_background_marching_map(), NG_MINIMAP_BACKGROUND_COLOR);


    main_fill_vert_array.setPrimitiveType(sf::PrimitiveType::Triangles);
    transformed_main_fill_vert_array.setPrimitiveType(sf::PrimitiveType::Triangles);
    pins_vert_array.setPrimitiveType(sf::PrimitiveType::Quads);
    transformed_pins_vert_array.setPrimitiveType(sf::PrimitiveType::Quads);
    fog_vert_array.setPrimitiveType(sf::PrimitiveType::Triangles);
    transformed_fog_vert_array.setPrimitiveType(sf::PrimitiveType::Triangles);
    background_vert_array.setPrimitiveType(sf::PrimitiveType::Triangles);
    transformed_background_vert_array.setPrimitiveType(sf::PrimitiveType::Triangles);

    fog_vert_array.clear();
    Planetoid::assemble_vert_array(fog_vert_array, MarchingMap(*base_miniature->get_scaled_fog_noisemap(), 0.5, true), palette.light);
}


void Minimap_UIContent::set_position(sf::Vector2f position) {
    this->position = position;
    dirty_transform = true;
}

void Minimap_UIContent::set_origin(sf::Vector2f origin) {
    this->origin = origin;
    dirty_transform = true;
}

sf::FloatRect Minimap_UIContent::get_bounds() {
    return transformed_main_fill_vert_array.getBounds();
}

void Minimap_UIContent::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(transformed_background_vert_array, states);
    target.draw(transformed_main_fill_vert_array, states);
    target.draw(transformed_pins_vert_array, states);
    target.draw(transformed_fog_vert_array, states);
}

void Minimap_UIContent::clean_transform() {
    apply_transform(main_fill_vert_array, transformed_main_fill_vert_array);
    apply_transform(fog_vert_array, transformed_fog_vert_array);
    apply_transform(pins_vert_array, transformed_pins_vert_array);
    apply_transform(background_vert_array, transformed_background_vert_array);
}

void Minimap_UIContent::prepare_for_draw() {
    UIContent::prepare_for_draw();
    if (dirty_transform) clean_transform();
}

void Minimap_UIContent::refresh_geometry(Player *player, std::vector<MinimapTraced_I *> traced_objects) {

    // refresh the pins
    pins_vert_array.clear();
    traced_objects.push_back(player);
    for (int i = 0; i < traced_objects.size(); ++i) {
        auto pos = traced_objects[i]->get_position_relative_to_planetoid();
        auto scaled_pos = pos / base_miniature->get_grid_size();

        for (auto vertex : traced_objects[i]->get_minimap_model_vertices()) {
            vertex.position += sf::Vector2f((std::floor(scaled_pos.x)+0.5), (-std::floor(scaled_pos.y)-0.5));
            pins_vert_array.append(vertex);
        }
    }

    // refresh the fog geometry if necessary
    auto palette = base_miniature->get_planetoid_persistent_data()->map_gen_info.palette;
    if (base_miniature->burn_fog(player->scene()->get_camera())) {
        fog_vert_array.clear();
        Planetoid::assemble_vert_array(fog_vert_array, MarchingMap(*base_miniature->get_scaled_fog_noisemap(), 0.5, true), palette.light);
    }

    dirty_transform = true;
}

void Minimap_UIContent::apply_transform(const sf::VertexArray &in, sf::VertexArray &out) {

    out.clear();
    for (int i = 0; i < in.getVertexCount(); ++i) {
        auto pos = in[i].position;
        out.append(in[i]);
        out[i].position = (sf::Vector2f(pos.x*NG_MINIMAP_SCALE_FACTOR, pos.y*NG_MINIMAP_SCALE_FACTOR) - origin + position);
    }
    dirty_transform = false;
}

