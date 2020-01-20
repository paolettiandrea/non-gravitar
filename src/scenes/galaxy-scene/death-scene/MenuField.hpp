#ifndef NON_GRAVITAR_MENUFIELD_HPP
#define NON_GRAVITAR_MENUFIELD_HPP


#include <SGE/logic/Logic.hpp>
#include <SGE/components/graphics/ui/UI.hpp>
#include <SGE/components/graphics/ui/blocks/UIText.hpp>


class MenuField : public sge::Logic {
public:
    MenuField(sge::UIText* m_text, sge::Alignment anchor_alignment = sge::Alignment(), sge::Alignment origin_alignment = sge::Alignment());

public:
    void on_start() override;

    std::string get_logic_id() override;

private:
    sge::UIText* text_content;

    sge::Alignment anchor_alignment;
    sge::Alignment origin_alignment;
};


#endif //NON_GRAVITAR_MENUFIELD_HPP
