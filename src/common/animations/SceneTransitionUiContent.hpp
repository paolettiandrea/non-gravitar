#ifndef NON_GRAVITAR_SCENETRANSITIONUICONTENT_HPP
#define NON_GRAVITAR_SCENETRANSITIONUICONTENT_HPP


#include <SGE/components/graphics/ui/blocks/UIContent.hpp>
#include <SFML/Graphics.hpp>

class SceneTransitionUIContent : public sge::UIContent {
public:
    void set_position(sf::Vector2f position) override;

    void set_origin(sf::Vector2f origin) override;

    sf::FloatRect get_bounds() override;

    void set_circle_radius(float radius);

    void set_circle_color(sf::Color color);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::CircleShape circle_shape;
};


#endif //NON_GRAVITAR_SCENETRANSITIONUICONTENT_HPP
