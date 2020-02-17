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
        sf::Color(161, 107, 53),
        sf::Color(136, 89, 42),
        sf::Color(221, 158, 97),
        sf::Color(111, 72, 32),
        sf::Color(255, 214, 173));

static const ColorPalette PLANETOID_HARD_PALETTE (
        sf::Color(98, 98, 101),
        sf::Color(82, 82, 84),
        sf::Color(139, 139, 144),
        sf::Color(64, 64, 65),
        sf::Color(174, 174, 177));

#define NG_CRATE_BACKGROUND_COLOR                   sf::Color(200,200,200)
# define NG_CRATE_PIN_COLOR                         PLAYER_PALETTE.dark

#define NG_PLAYER_UI_FUEL_BAR_COLOR                 PLAYER_PALETTE.dark
#define NG_PLAYER_UI_STAMINA_BAR_COLOR              PLAYER_PALETTE.light



#endif //NON_GRAVITAR_COLORS_HPP
