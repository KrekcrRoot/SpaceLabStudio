//
// Created by /<R3/<(RR00T on 09.05.2026.
//

#ifndef SPACELABSTUDIO_OBJECT_H
#define SPACELABSTUDIO_OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Sprite.h>

namespace SpaceLab::ui {


    class Object : public Sprite {

    public:
        virtual void render(render::Renderer* renderer) = 0;
        void draw(render::Renderer* renderer) override;
        void drawOutline(render::Renderer* renderer) const;
        void update(float deltaTime) override;

        [[nodiscard]] bool hit(const glm::vec2& pos) const override;
        void hover() override;
        void drop() override;
        void leave() override;
        void drag(const glm::vec2& delta) override;

        bool hovering() override;
        bool dragging() override;

        GLFWcursor* cursor() {
            return m_cursor;
        }

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

        GLFWcursor* m_cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);


    };

}

#endif //SPACELABSTUDIO_OBJECT_H
