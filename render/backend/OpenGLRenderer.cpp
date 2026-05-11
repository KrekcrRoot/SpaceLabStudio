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
layout(location = 1) in vec4 aColor;
uniform mat4 uProjection;
out vec4 vColor;
void main() {
    gl_Position = uProjection * vec4(aPos, 0.0, 1.0);
    vColor = aColor;
}
)glsl";

static const char* fragmentShaderSrc = R"glsl(
#version 330 core
in vec4 vColor;
out vec4 FragColor;
void main() {
    FragColor = vColor;
}
)glsl";

/*
 * OpenGLRenderer Geometric Functions
 * */

namespace SpaceLab {


    void OpenGLRenderer::drawRawLine(Vector4<float> pos, Vector4<float> fromColor, Vector4<float> toColor) {
        m_lineVertexBuffer.push_back(pos.x);
        m_lineVertexBuffer.push_back(pos.y);
        m_lineVertexBuffer.push_back(fromColor.x);
        m_lineVertexBuffer.push_back(fromColor.y);
        m_lineVertexBuffer.push_back(fromColor.z);
        m_lineVertexBuffer.push_back(fromColor.w);

        m_lineVertexBuffer.push_back(pos.z);
        m_lineVertexBuffer.push_back(pos.w);
        m_lineVertexBuffer.push_back(toColor.x);
        m_lineVertexBuffer.push_back(toColor.y);
        m_lineVertexBuffer.push_back(toColor.z);
        m_lineVertexBuffer.push_back(toColor.w);
    }

    void OpenGLRenderer::drawLine(Vector2<float> from, Vector2<float> to) {
        float r = 1.f, g = 1.f, b = 1.f;

        this->drawRawLine({
            from.x, from.y,
            to.x, to.y
        }, {r, g, b}, {r, g, b});
    }

    void OpenGLRenderer::drawLine(Vector2<float> from, Vector2<float> to, Vector3<float> color) {
        float r = color.x, g = color.y, b = color.z;

        this->drawRawLine({
            from.x, from.y,
            to.x, to.y
        }, {r, g, b, 1.f}, {r, g, b, 1.f});
    }


    void OpenGLRenderer::drawLine(Vector2<float> from, Vector2<float> to, Vector3<float> color, float alpha) {
        float r = color.x, g = color.y, b = color.z;

        this->drawRawLine({
            from.x, from.y,
            to.x, to.y
        }, {r, g, b, alpha}, {r, g, b, alpha});
    }

    void OpenGLRenderer::drawGradientLine(Vector4<float> pos, Vector4<float> fromColor, Vector4<float> toColor) {
        this->drawRawLine(pos, fromColor, toColor);
    }
}

namespace SpaceLab {

    static GLuint compileShader(GLenum type, const char* src) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "Shader compile error: " << infoLog << std::endl;
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    void OpenGLRenderer::init(void *handle) {

        if (!handle) {
            throw std::runtime_error("GLFW window handle is null");
        }

        m_window = static_cast<GLFWwindow*>(handle);
        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to init GLAD");
        }

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glfwGetFramebufferSize(m_window, &m_width, &m_height);
        glViewport(0, 0, m_width, m_height);

        m_projection = glm::ortho(0.f, static_cast<float>(m_width),
                                  0.f, static_cast<float>(m_height));

        setupShaders();
        setupBuffers();
        m_lineVertexBuffer.reserve(10000);

        std::cout << "[OpenGLRenderer] Initialized ("
                  << m_width << "x" << m_height << ")" << std::endl;
    }

    void OpenGLRenderer::setupShaders() {
        GLuint vert = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
        GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, vert);
        glAttachShader(m_shaderProgram, frag);
        glLinkProgram(m_shaderProgram);

        GLint success;
        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Program link error: " << infoLog << std::endl;
        }

        glDeleteShader(vert);
        glDeleteShader(frag);
    }

    void OpenGLRenderer::setupBuffers() {

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void*)(2 * sizeof(float)));

        glEnableVertexAttribArray(1);
        glBindVertexArray(0);

    }

    void OpenGLRenderer::setViewProjection(glm::mat4 projectionMatrix) {
        m_projection = projectionMatrix;
    }

    void OpenGLRenderer::beginFrame() {

        glClearColor(0.063,0.086,0.110, 1.f);
//        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_lineVertexBuffer.clear();

    }

    void OpenGLRenderer::endFrame() {
        flush();
    }

    void OpenGLRenderer::flush() {

        if(m_lineVertexBuffer.empty()) return;

        glUseProgram(m_shaderProgram);
        GLint projLoc = glGetUniformLocation(m_shaderProgram, "uProjection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_projection));

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     static_cast<GLsizeiptr>(m_lineVertexBuffer.size() * sizeof (float)),
                     m_lineVertexBuffer.data(),
                     GL_DYNAMIC_DRAW);

        auto vertexCount = static_cast<GLsizei>(m_lineVertexBuffer.size() / 6);
        glLineWidth(2.0f);
        glDrawArrays(GL_LINES, 0, vertexCount);

        glBindVertexArray(0);
        glUseProgram(0);

    }

    OpenGLRenderer::~OpenGLRenderer() {
        if (m_shaderProgram) glDeleteProgram(m_shaderProgram);
        if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO) glDeleteBuffers(1, &m_VBO);
    }

}