//
// Created by /<R3/<(RR00T on 13.05.2026.
//

#ifndef SPACELABSTUDIO_WIDGET_H
#define SPACELABSTUDIO_WIDGET_H

#include <glm/glm.hpp>

namespace SpaceLab::ui {

    class Widget {

    public:
        Widget(const glm::vec2& pos, const glm::vec2& size)
            : m_position(pos), m_size(size)
        {};
        virtual ~Widget() = default;

        virtual void draw() = 0;

        [[nodiscard]] bool hit(const glm::vec2& pos) const {
            return pos.x >= m_position.x &&
                    pos.x <= m_position.x + m_size.x &&
                    pos.y >= m_position.y &&
                    pos.y <= m_position.y + m_size.y;
        }

        [[nodiscard]] glm::vec2 getPosition() const {
            return m_position;
        }

        [[nodiscard]] glm::vec2 getSize() const {
            return m_size;
        };

    private:
        glm::vec2 m_position{}, m_size{};

    };

}

#endif //SPACELABSTUDIO_WIDGET_H
