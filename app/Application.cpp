//
// Created by /<R3/<(RR00T on 02.05.2026.
//

#include "Application.h"
#include <backend/OpenGLRenderer.h>
#include <GLFW/glfw3.h>

namespace SpaceLab {

    Application::Application() {
        m_renderer = new OpenGLRenderer();
        m_camera = new Camera(1280, 720);

        m_window = new Window{1280, 720, "SpaceLab Studio"};
        m_renderer->init(m_window->getNativeHandle());

    }

    void Application::run() {

        auto* handler = (GLFWwindow*) m_window->getNativeHandle();

        double lastTime = glfwGetTime();

        while (!glfwWindowShouldClose(handler))
        {

            double now = glfwGetTime();
            double deltaTime = now - lastTime;
            lastTime = now;

            m_camera->update(float(deltaTime));

            if(glfwGetKey(handler, GLFW_KEY_W) == GLFW_PRESS) {
                m_camera->push(0, 1);
            }
            if(glfwGetKey(handler, GLFW_KEY_D) == GLFW_PRESS) {
                m_camera->push(1, 0);
            }
            if(glfwGetKey(handler, GLFW_KEY_S) == GLFW_PRESS) {
                m_camera->push(0, -1);
            }
            if(glfwGetKey(handler, GLFW_KEY_A) == GLFW_PRESS) {
                m_camera->push(-1, 0);
            }

            bool leftDown = glfwGetMouseButton(handler, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

            if(leftDown && !m_leftBtnDown) {
                double mx, my;
                glfwGetCursorPos(handler, &mx, &my);
                auto worldPos = m_camera->screenToWorld(float(mx), float(my));
                m_camera->setTargetPosition(worldPos);
            }

            m_leftBtnDown = leftDown;

            m_renderer->setViewProjection(m_camera->getProjectionMatrix());
            m_renderer->beginFrame();

            m_renderer->drawGradientLine({
                0, 720.f / 2,
                1280, 720.f / 2
            }, {0.f, 0.f, 1.f}, {1.f, 0.f, 0.f});

            m_renderer->drawGradientLine({
                1280.f / 2, 0,
                1280.f / 2, 720
            }, {0.f, 1.f, 0.f}, {1.f, 0.f, 1.f});

            m_renderer->drawLine({0, 0}, {1280, 720}, {1.f, 0.f, 0.f});
            m_renderer->drawLine({0, 720}, {1280, 0}, {0.f, 1.f, 0.f});

            m_renderer->endFrame();

            /* Swap front and back buffers */
            glfwSwapBuffers(handler);

            /* Poll for and process events */
            glfwPollEvents();
        }


    }

    Application::~Application() {
        glfwTerminate();
        delete m_renderer;
        delete m_window;
        delete m_camera;
    }

}