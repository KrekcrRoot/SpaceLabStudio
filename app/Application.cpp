//
// Created by /<R3/<(RR00T on 02.05.2026.
//

#include "Application.h"
#include <backend/OpenGLRenderer.h>
#include <GLFW/glfw3.h>

namespace SpaceLab {

    Application::Application() {
        this->renderer = new OpenGLRenderer();

        window = new Window{1280, 720, "SpaceLab Studio"};
        this->renderer->init(window->getNativeHandle());

    }

    void Application::run() {

        auto* handler = (GLFWwindow*) this->window->getNativeHandle();

        while (!glfwWindowShouldClose(handler))
        {
            renderer->beginFrame();

            renderer->drawGradientLine({
                0, 720.f / 2,
                1280, 720.f / 2
            }, {0.f, 0.f, 1.f}, {1.f, 0.f, 0.f});

            renderer->drawGradientLine({
                1280.f / 2, 0,
                1280.f / 2, 720
            }, {0.f, 1.f, 0.f}, {1.f, 0.f, 1.f});

            renderer->drawLine({0, 0}, {1280, 720}, {1.f, 0.f, 0.f});
            renderer->drawLine({0, 720}, {1280, 0}, {0.f, 1.f, 0.f});

            renderer->endFrame();

            /* Swap front and back buffers */
            glfwSwapBuffers(handler);

            /* Poll for and process events */
            glfwPollEvents();
        }


    }

    Application::~Application() {
        glfwTerminate();
        delete this->renderer;
        delete this->window;
    }

}