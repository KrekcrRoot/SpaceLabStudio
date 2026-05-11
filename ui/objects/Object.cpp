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
        m_outlineAlphaTarget = 0.2f;
    }

    void Object::leave() {
        m_hover = false;
        m_outlineAlphaTarget = 0.f;
    }

    void Object::drag(const glm::vec2& pos) {

        if(!m_dragging) {
            m_hitPos = pos - m_position;
            std::cout << m_hitPos.x << " " << m_hitPos.y << "\n";
            m_dragging = true;
        }

        m_position = pos - m_hitPos;

    }

    void Object::drop() {
        m_dragging = false;
    }

    bool Object::dragging() {
        return m_dragging;
    }

    float Object::left() const {
        return m_position.x;
    }

    float Object::right() const {
        return m_position.x + m_width;
    }

    float Object::top() const {
        return m_position.y + m_height;
    }

    float Object::bottom() const {
        return m_position.y;
    }

    void Object::draw(SpaceLab::Renderer *renderer) {

        if(m_outlineAlpha > 0) {
            drawOutline(renderer);
        }

        render(renderer);

    }

    void Object::update(float deltaTime) {
        if(m_outlineAlpha < m_outlineAlphaTarget) {
            m_outlineAlpha += deltaTime * m_outlineFade;
            if(m_outlineAlpha > m_outlineAlphaTarget) m_outlineAlpha = m_outlineAlphaTarget;
        }
        if(m_outlineAlpha > m_outlineAlphaTarget) {
            m_outlineAlpha -= deltaTime * m_outlineFade;
            if(m_outlineAlpha < m_outlineAlphaTarget) m_outlineAlpha = m_outlineAlphaTarget;
        }
    }

    void Object::drawOutline(Renderer* renderer) const {

        Vector4<float> color = {1.f, 1.f, 1.f, m_outlineAlpha};

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