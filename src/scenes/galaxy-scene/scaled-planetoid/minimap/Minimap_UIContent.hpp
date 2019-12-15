#ifndef NON_GRAVITAR_MINIMAP_UICONTENT_HPP
#define NON_GRAVITAR_MINIMAP_UICONTENT_HPP


#include <SGE/components/graphics/ui/blocks/UIContent.hpp>
#include "MiniaturePlanetoid.hpp"
#include "MinimapTraced_I.hpp"

#define NG_MINIMAP_SCALE_FACTOR 4


class Minimap_UIContent : public sge::UIContent {
public:
    explicit Minimap_UIContent(MiniaturePlanetoid* original);

    void set_position(sf::Vector2f position) override;

    void set_origin(sf::Vector2f origin) override;

    sf::FloatRect get_bounds() override;

    void refresh_pins(std::vector<MinimapTraced_I*> traced_objects);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    MiniaturePlanetoid* base_miniature;

    sf::VertexArray main_fill_vert_array;
    sf::VertexArray transformed_main_fill_vert_array;

    sf::VertexArray pins_vert_array;

    sf::Vector2f origin = sf::Vector2f(0, 0);
    sf::Vector2f position = sf::Vector2f(0, 0);
    bool dirty_transform = true;

    void clean_transform();

public:
    void prepare_for_draw() override;

};


#endif //NON_GRAVITAR_MINIMAP_UICONTENT_HPP
