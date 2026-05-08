//
// Created by /<R3/<(RR00T on 03.05.2026.
//

#include "OpenGLRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace SpaceLab {

    void OpenGLRenderer::init(void *handle) {

        if (!handle) {
            throw std::runtime_error("GLFW window handle is null");
        }

        auto* window = (GLFWwindow*) handle;
        glfwMakeContextCurrent(window);
        

    }

    void OpenGLRenderer::drawLine(Vector2<float> from, Vector2<float> to) {

    }

    void OpenGLRenderer::beginFrame() {

        glClearColor(0.19f, 0.18f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

    }

    void OpenGLRenderer::endFrame() {}

    void OpenGLRenderer::flush() {}

}