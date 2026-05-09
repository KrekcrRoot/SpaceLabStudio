//
// Created by /<R3/<(RR00T on 09.05.2026.
//

#ifndef SPACELABSTUDIO_OBJECT_H
#define SPACELABSTUDIO_OBJECT_H

#include <Sprite.h>

namespace SpaceLab::ui {

    class Object : public Sprite {

    public:
        virtual void render(Renderer* renderer) = 0;
        void draw(Renderer* renderer) override;
        void drawOutline(Renderer* renderer) const;

        [[nodiscard]] bool hit(const glm::vec2& pos) const override;
        void hover() override;
        void leave() override;
        void drag() override;


    protected:
        glm::vec2 m_position {};
        float m_width{}, m_height{};


        float m_outline = 5.f;


    };

}

#endif //SPACELABSTUDIO_OBJECT_H
