//
// Created by /<R3/<(RR00T on 11.05.2026.
//

#include <objects/TextObject.h>
#include <utility>

namespace SpaceLab::ui {

    TextObject::TextObject(render::font::Font *font, std::string str)
        : m_text(std::move(str)), m_font(font)
    {
        auto size = m_font->measureString(m_text);
        m_width = size.x;
        m_height = size.y;
    }

    TextObject::TextObject(render::font::Font *font, std::string str, Vector2<float> pos)
        : m_text(std::move(str)), m_font(font)
    {
        m_position = {pos.x, pos.y};
        auto size = m_font->measureString(m_text);
        m_width = size.x;
        m_height = size.y;
    }

    void TextObject::render(render::Renderer *renderer)
    {
        renderer->drawString(*m_font, m_text, {
            m_position.x, m_position.y
        });
    }

}