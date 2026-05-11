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
        void update(float deltaTime) override;

        [[nodiscard]] bool hit(const glm::vec2& pos) const override;
        void hover() override;
        void leave() override;
        void drag(const glm::vec2& delta) override;
        bool dragging() override;
        void drop() override;

        //borders
        [[nodiscard]] float left() const;
        [[nodiscard]] float right() const;
        [[nodiscard]] float top() const;
        [[nodiscard]] float bottom() const;



    protected:
        glm::vec2 m_position {};
        glm::vec2 m_hitPos {};
        float m_width{}, m_height{};

        float m_outline = 5.f;
        float m_outlineFade = 3.f;
        float m_outlineAlpha = 0.f;
        float m_outlineAlphaTarget = 0.f;


    };

}

#endif //SPACELABSTUDIO_OBJECT_H
