#ifndef NON_GRAVITAR_COLORS_HPP
#define NON_GRAVITAR_COLORS_HPP

#include <ColorPalette.hpp>

static const ColorPalette PLAYER_PALETTE (
        sf::Color(40, 160, 40),
        sf::Color(40, 120, 40),
        sf::Color(45, 218, 45),
        sf::Color(0, 68, 0),
        sf::Color(136, 204, 136));


static const ColorPalette BASIC_ENEMY_PALETTE (
        sf::Color(202, 40, 27),
        sf::Color(255, 62, 47),
        sf::Color(190, 100, 40),
        sf::Color(70, 50, 0),
        sf::Color(136, 204, 136));

static const ColorPalette SNIPER_ENEMY_PALETTE (
        sf::Color(160, 100, 100),
        sf::Color(140, 100, 100),
        sf::Color(190, 100, 100),
        sf::Color(70, 50, 100),
        sf::Color(136, 204, 100));


#define NG_COLORS_EASY_PLANETOID sf::Color(40, 160, 40), sf::Color(40, 120, 40), sf::Color(45, 218, 45), sf::Color(0, 68, 0), sf::Color(136, 204, 136)

# define NG_CRATE_PIN_COLOR sf::Color(100,100,100)



#endif //NON_GRAVITAR_COLORS_HPP
