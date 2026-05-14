//
// Created by /<R3/<(RR00T on 14.05.2026.
//

#include <widgets/ButtonWidget.h>

namespace SpaceLab::ui {

    ButtonWidget::ButtonWidget(const glm::vec2 &pos, const glm::vec2 &size)
        : Widget(pos, size)
    {}

    const std::string &ButtonWidget::getText() const {
        return m_text;
    }

    void ButtonWidget::setText(const std::string &text) {
        m_text = text;
    }

    void ButtonWidget::draw(render::Renderer *renderer) {

        renderer->drawLine({
            getPosition().x,
            getPosition().y
        }, {
            getPosition().x + getSize().x,
            getPosition().y + getSize().y
        });

    }

}