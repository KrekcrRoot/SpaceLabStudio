//
// Created by /<R3/<(RR00T on 08.05.2026.
//

#ifndef SPACELABSTUDIO_CAMERA_H
#define SPACELABSTUDIO_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SpaceLab {

    class Camera {

    public:
        Camera(float viewWidth, float viewHeight);
        [[nodiscard]] glm::mat4 getProjectionMatrix() const;
        void push(float x, float y);
        void update(float deltaTime);
        void zoom(float delta);

        [[nodiscard]] glm::vec2 screenToWorld(float screenX, float screenY) const;
        [[nodiscard]] glm::vec2 worldToScreen(const glm::vec2& worldPos) const;

        void setTargetPosition(const glm::vec2& pos);

        [[nodiscard]] float top() const;
        [[nodiscard]] float left() const;
        [[nodiscard]] float bottom() const;
        [[nodiscard]] float right() const;

    private:
        glm::vec2 m_targetPosition {};
        glm::vec2 m_position {};


        float m_zoom = 1.f;
        float m_targetZoom = 1.f;

        float m_smoothness = 8.0f;
        float m_viewWidth = 1280.f, m_viewHeight = 720.f;


    };

}



#endif //SPACELABSTUDIO_CAMERA_H
