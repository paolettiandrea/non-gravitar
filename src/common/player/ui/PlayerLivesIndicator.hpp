#ifndef NON_GRAVITAR_PLAYERLIVESINDICATOR_HPP
#define NON_GRAVITAR_PLAYERLIVESINDICATOR_HPP


#include <SGE/components/graphics/ui/blocks/UIContent.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#define NG_PLAYER_UI_LIVES_LOGO_PATH "./res/models/player/player_ship__body.smesh"
#define NG_PLAYER_UI_LIVES_INDICATOR_LOGO_SIZE 8.5
#define NG_PLAYER_UI_LIVES_INDICATOR_LOGO_SPACING 4

class PlayerLivesIndicator : public sge::UIContent {
public:
    explicit PlayerLivesIndicator(unsigned int lives_number);
    void set_position(sf::Vector2f position) override;

    void set_origin(sf::Vector2f origin) override;

    sf::FloatRect get_bounds() override;

    void set_lives(unsigned int new_lives_number);

    void prepare_for_draw() override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Vector2f position;
    sf::Vector2f origin;

    unsigned int lives_number = 0;

    sf::VertexArray transformed_geometry_vert_array;
    sf::VertexArray geometry_vert_array;

    void update_geometry();
};


#endif //NON_GRAVITAR_PLAYERLIVESINDICATOR_HPP
