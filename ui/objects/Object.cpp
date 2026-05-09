//
// Created by /<R3/<(RR00T on 09.05.2026.
//

#include <objects/Object.h>

namespace SpaceLab::ui {

    bool Object::hit(const glm::vec2 &pos) const {
        bool hitX = pos.x >= m_position.x && pos.x <= m_position.x + m_width;
        bool hitY = pos.y >= m_position.y && pos.y <= m_position.y + m_height;

        return hitX && hitY;
    }

    void Object::hover() {
        m_hover = true;
    }

    void Object::leave() {
        m_hover = false;
    }

    void Object::drag() {}

    void Object::draw(SpaceLab::Renderer *renderer) {

        if(m_hover) {
            drawOutline(renderer);
        }

        render(renderer);

    }

    void Object::drawOutline(Renderer* renderer) const {

        Vector4<float> color = {1.f, 1.f, 1.f, 1.f};

        renderer->drawGradientLine({
            m_position.x - m_outline, m_position.y - m_outline,
            m_position.x - m_outline, m_position.y + m_height + m_outline,
        }, color, color);

        renderer->drawGradientLine({
            m_position.x - m_outline, m_position.y + m_height + m_outline,
            m_position.x + m_width + m_outline, m_position.y + m_height + m_outline,
        }, color, color);

        renderer->drawGradientLine({
            m_position.x + m_width + m_outline, m_position.y + m_height + m_outline,
            m_position.x + m_width + m_outline, m_position.y - m_outline,
        }, color, color);

        renderer->drawGradientLine({
            m_position.x + m_width + m_outline, m_position.y - m_outline,
            m_position.x - m_outline, m_position.y - m_outline,
        }, color, color);

    }

}