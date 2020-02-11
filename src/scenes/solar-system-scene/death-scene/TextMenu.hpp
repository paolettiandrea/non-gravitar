#ifndef NON_GRAVITAR_TEXTMENU_HPP
#define NON_GRAVITAR_TEXTMENU_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/ui/UI.hpp>
#include <SGE/components/graphics/ui/blocks/UIText.hpp>

#define NG_MENU_FONT "ARCADE_R"


class TextMenu : public sge::Logic {
protected:
    void add_text(std::string label, const std::string& font_id, unsigned int char_size, sf::Vector2f offset);
};


#endif //NON_GRAVITAR_TEXTMENU_HPP
