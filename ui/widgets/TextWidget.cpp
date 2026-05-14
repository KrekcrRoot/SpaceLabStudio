//
// Created by /<R3/<(RR00T on 13.05.2026.
//

#include <widgets/TextWidget.h>

namespace SpaceLab::ui {

    TextWidget::TextWidget(const render::font::Font &font, const glm::vec2 &pos, const std::string &str)
        : Widget(pos, font.measureString(str)), m_font(font), m_text(str)
    {}

    void TextWidget::draw(render::Renderer *renderer) {

        renderer->drawString(m_font, m_text, {
            getPosition().x,
            getPosition().y,
        });

    }

}