//
// Created by /<R3/<(RR00T on 03.05.2026.
//

#ifndef SPACELABSTUDIO_OPENGLRENDERER_H
#define SPACELABSTUDIO_OPENGLRENDERER_H

#include <Renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace SpaceLab {

    class OpenGLRenderer : public Renderer {

    public:
        OpenGLRenderer() = default;
        ~OpenGLRenderer() override;

        void init(void *nativeWindow) override;


        // LINES
        void drawRawLine(Vector4<float> pos, Vector3<float> fromColor, Vector3<float> toColor);
        void drawLine(Vector2<float> from, Vector2<float> to) override;
        void drawLine(Vector2<float> from, Vector2<float> to, Vector3<float> color) override;
        void drawGradientLine(Vector4<float> pos, Vector3<float> fromColor, Vector3<float> toColor) override;


        void setViewProjection(glm::mat4 projectionMatrix) override;
        void beginFrame() override;
        void endFrame() override;

    private:
        void flush() override;
        void setupShaders();
        void setupBuffers();

        GLFWwindow* m_window = nullptr;
        int m_width = 1280;
        int m_height = 720;

        GLuint m_shaderProgram = 0;
        GLuint m_VAO = 0;
        GLuint m_VBO = 0;

        glm::mat4 m_projection{};
        std::vector<float> m_lineVertexBuffer;

    };

}

#endif //SPACELABSTUDIO_OPENGLRENDERER_H
