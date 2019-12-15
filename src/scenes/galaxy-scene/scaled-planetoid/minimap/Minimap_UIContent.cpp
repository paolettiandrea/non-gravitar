#include "Minimap_UIContent.hpp"

Minimap_UIContent::Minimap_UIContent(MiniaturePlanetoid *original) {
    base_miniature = original;
    auto palette = original->get_planetoid_persistent_data()->map_gen_info.palette;

    Planetoid::assemble_vert_array(main_fill_vert_array, *original->get_scaled_marching_map(), palette.primary);
    Planetoid::assemble_vert_array(transformed_main_fill_vert_array, *original->get_scaled_marching_map(), palette.primary);
    Planetoid::assemble_vert_array(main_fill_vert_array, *original->get_scaled_secondary_marching_map(), palette.dark);
    Planetoid::assemble_vert_array(transformed_main_fill_vert_array, *original->get_scaled_secondary_marching_map(), palette.dark);
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
    target.draw(transformed_main_fill_vert_array, states);
    target.draw(pins_vert_array, states);
}

void Minimap_UIContent::clean_transform() {
    for (int i = 0; i < main_fill_vert_array.getVertexCount(); ++i) {
        auto pos = main_fill_vert_array[i].position;
        transformed_main_fill_vert_array[i].position = (sf::Vector2f(pos.x*NG_MINIMAP_SCALE_FACTOR, pos.y*NG_MINIMAP_SCALE_FACTOR) - origin + position);
        dirty_transform = false;
    }
}

void Minimap_UIContent::prepare_for_draw() {
    UIContent::prepare_for_draw();
    if (dirty_transform) clean_transform();
}

void Minimap_UIContent::refresh_pins(std::vector<MinimapTraced_I*> traced_objects) {
    pins_vert_array.clear();
    pins_vert_array.setPrimitiveType(sf::PrimitiveType::Quads);
    for (int i = 0; i < traced_objects.size(); ++i) {

        auto pos = traced_objects[i]->get_position_relative_to_planetoid();
        auto scaled_pos = pos / base_miniature->get_grid_size();

        for (auto vertex : traced_objects[i]->get_minimap_model_vertices()) {
            vertex.position += sf::Vector2f((std::floor(scaled_pos.x)+0.5)*NG_MINIMAP_SCALE_FACTOR, (-std::floor(scaled_pos.y)-0.5)*NG_MINIMAP_SCALE_FACTOR) - origin + position;

            pins_vert_array.append(vertex);
        }
    }
}

