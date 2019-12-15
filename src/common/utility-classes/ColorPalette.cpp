#include "ColorPalette.hpp"

ColorPalette::ColorPalette(const sf::Color &primary, const sf::Color &dark,
                           const sf::Color &light, const sf::Color &darker,
                           const sf::Color &lighter) : primary(primary), dark(dark),
                                                       light(light),
                                                       darker(darker),
                                                       lighter(lighter) {

}
