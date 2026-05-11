//
// Created by /<R3/<(RR00T on 03.05.2026.
//

#ifndef SPACELABSTUDIO_OPENGLRENDERER_H
#define SPACELABSTUDIO_OPENGLRENDERER_H

#include <Renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace SpaceLab::render {

    class OpenGLRenderer : public Renderer {

    public:
        OpenGLRenderer() = default;
        ~OpenGLRenderer() override;

        void init(void *nativeWindow) override;


        // LINES
        void drawRawLine(Vector4<float> pos, Vector4<float> fromColor, Vector4<float> toColor);
        void drawLine(Vector2<float> from, Vector2<float> to) override;
        void drawLine(Vector2<float> from, Vector2<float> to, Vector3<float> color) override;
        void drawLine(Vector2<float> from, Vector2<float> to, Vector3<float> color, float alpha) override;
        void drawGradientLine(Vector4<float> pos, Vector4<float> fromColor, Vector4<float> toColor) override;

        // Text Rendering
        void drawString(const font::Font& font, const std::string& str, Vector2<float> pos) override;

        void setViewProjection(glm::mat4 projectionMatrix) override;
        void beginFrame() override;
        void endFrame() override;

    private:
        void flush() override;
        void setupShaders();
        void setupBuffers();
        void setupTexShaders();
        void setupTexBuffers();
        void flushText();

        GLFWwindow* m_window = nullptr;
        int m_width = 1280;
        int m_height = 720;

        GLuint m_shaderProgram = 0;
        GLuint m_VAO = 0;
        GLuint m_VBO = 0;

        GLuint m_shaderTexProgram = 0;  // шейдер для текстур
        GLuint m_VAOtex = 0, m_VBOtex = 0;
        std::vector<float> m_texVertices;      // батч для текстур (x,y,u,v)
        GLuint m_currentTexture = 0;

        glm::mat4 m_projection{};
        std::vector<float> m_lineVertexBuffer;

    };

}

#endif //SPACELABSTUDIO_OPENGLRENDERER_H
