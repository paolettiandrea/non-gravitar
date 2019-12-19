#include <SGE/components/graphics/VertArray.hpp>
#include "PlayerLivesIndicator.hpp"

void PlayerLivesIndicator::set_position(sf::Vector2f position) {
    this->position = position;
}

void PlayerLivesIndicator::set_origin(sf::Vector2f origin) {
    this->origin = origin;
}

sf::FloatRect PlayerLivesIndicator::get_bounds() {
    return geometry_vert_array.getBounds();
}

void PlayerLivesIndicator::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(transformed_geometry_vert_array, states);
}

PlayerLivesIndicator::PlayerLivesIndicator(unsigned int lives_number) {
    transformed_geometry_vert_array.setPrimitiveType(sf::PrimitiveType::Triangles);
    set_lives(lives_number);
}

void PlayerLivesIndicator::prepare_for_draw() {
    update_geometry();
}

void PlayerLivesIndicator::set_lives(unsigned int new_lives_number) {
    if (new_lives_number != lives_number) {
        geometry_vert_array.clear();

        for (int i = 0; i < new_lives_number; ++i) {
            sge::cmp::VertArray::append_smesh_to_sf_vertex_array(geometry_vert_array, NG_PLAYER_UI_LIVES_LOGO_PATH,
                    sf::Vector2f((NG_PLAYER_UI_LIVES_INDICATOR_LOGO_SIZE*2.0 + NG_PLAYER_UI_LIVES_INDICATOR_LOGO_SPACING)*i, 0),
                    NG_PLAYER_UI_LIVES_INDICATOR_LOGO_SIZE);
        }

        make_bounds_dirty();
        lives_number = new_lives_number;
    }
}

void PlayerLivesIndicator::update_geometry() {
    transformed_geometry_vert_array.clear();
    for (int j = 0; j < geometry_vert_array.getVertexCount(); ++j) {
        transformed_geometry_vert_array.append(geometry_vert_array[j]);
        transformed_geometry_vert_array[j].position = geometry_vert_array[j].position - origin + position;
    }
}
