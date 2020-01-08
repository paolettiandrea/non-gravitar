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
        sf::Color(160, 100, 40),
        sf::Color(140, 100, 40),
        sf::Color(190, 100, 40),
        sf::Color(70, 50, 0),
        sf::Color(136, 204, 136));

#define NG_COLORS_PLAYER sf::Color(40, 160, 40), sf::Color(40, 120, 40), sf::Color(45, 218, 45), sf::Color(0, 68, 0), sf::Color(136, 204, 136)
#define NG_COLORS_FUEL
#define NG_COLORS_STAMINA


#define NG_COLORS_EASY_PLANETOID sf::Color(40, 160, 40), sf::Color(40, 120, 40), sf::Color(45, 218, 45), sf::Color(0, 68, 0), sf::Color(136, 204, 136)
#define NG_COLORS_MEDIUM_PLANETOID sf::Color(40, 160, 40), sf::Color(40, 120, 40), sf::Color(45, 218, 45), sf::Color(0, 68, 0), sf::Color(136, 204, 136)
#define NG_COLORS_HARD_PLANETOID sf::Color(40, 160, 40), sf::Color(40, 120, 40), sf::Color(45, 218, 45), sf::Color(0, 68, 0), sf::Color(136, 204, 136)

#define NG_COLORS_BASIC_ENEMY sf::Color(40, 160, 40), sf::Color(40, 120, 40), sf::Color(45, 218, 45), sf::Color(0, 68, 0), sf::Color(136, 204, 136)
#define NG_COLORS_MULTISHOT_ENEMY sf::Color(40, 160, 40), sf::Color(40, 120, 40), sf::Color(45, 218, 45), sf::Color(0, 68, 0), sf::Color(136, 204, 136)
#define NG_COLORS_SNIPER_ENEMY sf::Color(40, 160, 40), sf::Color(40, 120, 40), sf::Color(45, 218, 45), sf::Color(0, 68, 0), sf::Color(136, 204, 136)


# define NG_CRATE_PIN_COLOR sf::Color(100,100,100)



#endif //NON_GRAVITAR_COLORS_HPP
