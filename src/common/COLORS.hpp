#ifndef NON_GRAVITAR_COLORS_HPP
#define NON_GRAVITAR_COLORS_HPP

#include <ColorPalette.hpp>

#define UI_FONT "ARCADE_R"

#define NG_BACKGROUND_COLOR sf::Color(10,10,10)

static const ColorPalette PLAYER_PALETTE (
        sf::Color(27, 70, 169),
        sf::Color(23, 54, 125),
        sf::Color( 51, 94, 194),
        sf::Color(13, 34, 83),
        sf::Color(100, 150, 220));

// ENEMIES  -----------------------------------------------------------------------------------------------------------

static const ColorPalette SNIPER_ENEMY_PALETTE (
        sf::Color(224, 29, 29),
        sf::Color(167, 27, 27),
        sf::Color(252, 55, 55),
        sf::Color(104, 28, 28),
        sf::Color(255, 70, 70));

static const ColorPalette BASIC_ENEMY_PALETTE (
        sf::Color(224, 166, 29),
        sf::Color(167, 125, 27),
        sf::Color(252, 193, 55),
        sf::Color(104, 82, 28),
        sf::Color(255, 200, 70));

// PLANETOIDS   -------------------------------------------------------------------------------------------------------

static const ColorPalette PLANETOID_EASY_PALETTE (
        sf::Color(40, 136, 40),
        sf::Color(30, 113, 30),
        sf::Color(72, 180, 72),
        sf::Color(24, 93, 24),
        sf::Color(128, 207, 128));

static const ColorPalette PLANETOID_MEDIUM_PALETTE (
        sf::Color(101, 90, 37),
        sf::Color(75, 65, 18),
        sf::Color(117, 108, 64),
        sf::Color(46, 39, 3),
        sf::Color(169, 157, 100));

static const ColorPalette PLANETOID_HARD_PALETTE (
        
        sf::Color(34, 35, 38),
        sf::Color(14, 16, 19),
        sf::Color(58, 59, 60),
        sf::Color(11, 13, 19),
        sf::Color(84, 84, 84));

#define NG_CRATE_BACKGROUND_COLOR                   sf::Color(180,180,200)
# define NG_CRATE_PIN_COLOR                         PLAYER_PALETTE.dark

#define NG_PLAYER_UI_FUEL_BAR_COLOR                 PLAYER_PALETTE.dark
#define NG_PLAYER_UI_STAMINA_BAR_COLOR              PLAYER_PALETTE.light



#endif //NON_GRAVITAR_COLORS_HPP
