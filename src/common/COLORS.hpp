#ifndef NON_GRAVITAR_COLORS_HPP
#define NON_GRAVITAR_COLORS_HPP

#include <ColorPalette.hpp>

#define UI_FONT "ARCADE_R"

static const ColorPalette PLAYER_PALETTE (
        sf::Color(27, 55,107),
        sf::Color(53,108,209),
        sf::Color( 34, 78,158),
        sf::Color(14, 31, 60),
        sf::Color(100, 100, 200));

// ENEMIES  -----------------------------------------------------------------------------------------------------------

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

// PLANETOIDS   -------------------------------------------------------------------------------------------------------

static const ColorPalette PLANETOID_EASY_PALETTE (
        sf::Color(40, 160, 40),
        sf::Color(40, 120, 40),
        sf::Color(45, 218, 45),
        sf::Color(0, 68, 0),
        sf::Color(136, 204, 136));

static const ColorPalette PLANETOID_MEDIUM_PALETTE (
        sf::Color(0, 169, 169),
        sf::Color(0, 114, 114),
        sf::Color(0, 114, 114),
        sf::Color(50,0,0),
        sf::Color(136, 204, 100));

static const ColorPalette PLANETOID_HARD_PALETTE (
        sf::Color(255, 124, 0),
        sf::Color(230, 112, 0),
        sf::Color(255, 124, 0),
        sf::Color(70, 50, 100),
        sf::Color(136, 204, 100));


# define NG_CRATE_PIN_COLOR sf::Color(100,100,100)



#endif //NON_GRAVITAR_COLORS_HPP
