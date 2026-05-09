//
// Created by /<R3/<(RR00T on 09.05.2026.
//

#include <objects/NumberObject.h>

namespace SpaceLab::ui {

    NumberObject::NumberObject(const glm::vec2& pos, float length) {
        m_position = pos;
        m_width = length;
        m_height = length;
    }

    void NumberObject::render(Renderer* renderer) {

        renderer->drawLine(
            {m_position.x, m_position.y},
            {m_position.x + m_width, m_position.y + m_height},
            {1.f, 1.f, 1.f}
        );

    }

}