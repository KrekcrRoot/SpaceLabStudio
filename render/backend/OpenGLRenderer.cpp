//
// Created by /<R3/<(RR00T on 03.05.2026.
//

#include "OpenGLRenderer.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Исходники шейдеров (2D, позиция + цвет)
static const char* vertexShaderSrc = R"glsl(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
uniform mat4 uProjection;
out vec3 vColor;
void main() {
    gl_Position = uProjection * vec4(aPos, 0.0, 1.0);
    vColor = aColor;
}
)glsl";

static const char* fragmentShaderSrc = R"glsl(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(vColor, 1.0);
}
)glsl";

namespace SpaceLab {

    void OpenGLRenderer::init(void *handle) {

        if (!handle) {
            throw std::runtime_error("GLFW window handle is null");
        }

        m_window = static_cast<GLFWwindow*>(handle);
        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to init GLAD");
        }

        glfwGetFramebufferSize(m_window, &m_width, &m_height);
        glViewport(0, 0, m_width, m_height);

        m_projection = glm::ortho(0.f, static_cast<float>(m_width),
                                  0.f, static_cast<float>(m_height));

        setupShaders();
        setupBuffers();

        std::cout << "[OpenGLRenderer] Initialized ("
                  << m_width << "x" << m_height << ")" << std::endl;
    }

    void OpenGLRenderer::drawLine(Vector2<float> from, Vector2<float> to) {

    }

    void OpenGLRenderer::beginFrame() {

        glClearColor(0.19f, 0.18f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

    }

    void OpenGLRenderer::endFrame() {}

    void OpenGLRenderer::flush() {}

    OpenGLRenderer::~OpenGLRenderer() {

    };

}