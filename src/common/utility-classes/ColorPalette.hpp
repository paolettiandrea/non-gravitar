#ifndef NON_GRAVITAR_COLORPALETTE_HPP
#define NON_GRAVITAR_COLORPALETTE_HPP

#include <SFML/Graphics.hpp>

class ColorPalette {
public:
    ColorPalette(const sf::Color &primary, const sf::Color &dark, const sf::Color &light,
                 const sf::Color &darker, const sf::Color &lighter);

    sf::Color primary;
    sf::Color dark;
    sf::Color light;
    sf::Color darker;
    sf::Color lighter;
};


#endif //NON_GRAVITAR_COLORPALETTE_HPP
