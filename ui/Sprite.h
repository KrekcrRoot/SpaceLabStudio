//
// Created by /<R3/<(RR00T on 09.05.2026.
//

#ifndef SPACELABSTUDIO_SPRITE_H
#define SPACELABSTUDIO_SPRITE_H

#include <Renderer.h>

namespace SpaceLab::ui {

    class Sprite {

    public:
        virtual void draw(Renderer* renderer) = 0;
        virtual ~Sprite() = default;

        [[nodiscard]] virtual bool hit(const glm::vec2& pos) const = 0;
        virtual void update(float deltaTime) = 0;
        virtual void hover() = 0;
        virtual void leave() = 0;
        virtual void drag(const glm::vec2& delta) = 0;
        virtual void drop() = 0;
        virtual bool dragging() = 0;

        bool m_dragging = false;
        bool m_hover = false;

    private:

    };

}

#endif //SPACELABSTUDIO_SPRITE_H
