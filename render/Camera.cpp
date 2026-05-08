//
// Created by /<R3/<(RR00T on 08.05.2026.
//

#include "Camera.h"

namespace SpaceLab {

    Camera::Camera(float viewWidth, float viewHeight) : m_viewWidth(viewWidth), m_viewHeight(viewHeight) {}

    glm::vec2 Camera::screenToWorld(float screenX, float screenY) const {

        float halfW = m_viewWidth * 0.5f * m_zoom;
        float halfH = m_viewHeight * 0.5f * m_zoom;

        float worldX = m_position.x - halfW + screenX * m_zoom;
        float worldY = m_position.y + halfH - screenY * m_zoom;

        return {worldX, worldY};

    }

    glm::vec2 Camera::worldToScreen(const glm::vec2 &worldPos) const {}

    void Camera::setTargetPosition(const glm::vec2 &pos) {
        m_targetPosition = pos;
//        m_position = pos;
    }

    glm::mat4 Camera::getProjectionMatrix() const {
        float halfW = m_viewWidth * 0.5f * m_zoom;
        float halfH = m_viewHeight * 0.5f * m_zoom;

        return glm::ortho(m_position.x - halfW, m_position.x + halfW,
                          m_position.y - halfH, m_position.y + halfH);
    }

    void Camera::push(float x, float y) {
        float speed = 3.f;
        m_targetPosition += glm::vec2(x * speed, y * speed);
    }

    void Camera::update(float deltaTime) {
        float lerpFactor = 1.0f - std::exp(-m_smoothness * deltaTime);
        m_position = glm::mix(m_position, m_targetPosition, lerpFactor);
    }


    float Camera::left() const {
        float halfW = m_viewWidth * 0.5f * m_zoom;
        return m_position.x - halfW;
    }

    float Camera::right() const {
        float halfW = m_viewWidth * 0.5f * m_zoom;
        return m_position.x + halfW;
    }

    float Camera::top() const {
        float halfH = m_viewHeight * 0.5f * m_zoom;
        return m_position.y - halfH;
    }

    float Camera::bottom() const {
        float halfH = m_viewHeight * 0.5f * m_zoom;
        return m_position.y + halfH;
    }

}