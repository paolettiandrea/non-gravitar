#include "SceneTransitionUiContent.hpp"

void SceneTransitionUIContent::set_position(sf::Vector2f position) {
    circle_shape.setPosition(position);
    make_bounds_dirty();
}

void SceneTransitionUIContent::set_origin(sf::Vector2f origin) {
    circle_shape.setOrigin(origin);
    make_bounds_dirty();
}

sf::FloatRect SceneTransitionUIContent::get_bounds() {
    return circle_shape.getLocalBounds();
}

void SceneTransitionUIContent::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (circle_shape.getRadius()>0)
        target.draw(circle_shape, states);
}

void SceneTransitionUIContent::set_circle_radius(float radius) {
    circle_shape.setRadius(radius);
    make_bounds_dirty();
}

void SceneTransitionUIContent::set_circle_color(sf::Color color) {
    circle_shape.setFillColor(color);
}
