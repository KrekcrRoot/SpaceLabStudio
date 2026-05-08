//
// Created by /<R3/<(RR00T on 02.05.2026.
//

#include "Application.h"
#include <backend/OpenGLRenderer.h>
#include <GLFW/glfw3.h>
#include <cmath>

namespace SpaceLab {

    using clock = std::chrono::high_resolution_clock;

    Application::Application() {
        m_renderer = new OpenGLRenderer();
        m_camera = new Camera(1280, 720);

        m_window = new Window{1280, 720, "SpaceLab Studio"};
        m_renderer->init(m_window->getNativeHandle());

    }

    void Application::run() {

        auto* handler = (GLFWwindow*) m_window->getNativeHandle();

        auto lastTime = clock::now();

        while (!glfwWindowShouldClose(handler))
        {

            auto now = clock::now();
            double dt = std::chrono::duration<float>(now - lastTime).count();
            lastTime = now;

            handleInput();

            m_camera->update(float(dt));

            m_renderer->setViewProjection(m_camera->getProjectionMatrix());
            m_renderer->beginFrame();

            m_infiniteGrid.render(m_renderer, m_camera);

            m_renderer->endFrame();

            glfwSwapBuffers(handler);
            glfwPollEvents();
        }


    }

    void Application::handleInput() {

        auto window = static_cast<GLFWwindow*>(m_window->getNativeHandle());

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            m_camera->push(0, 1);
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            m_camera->push(1, 0);
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            m_camera->push(0, -1);
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            m_camera->push(-1, 0);
        }

        bool leftDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

        if(leftDown && !m_leftBtnDown) {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);
            auto worldPos = m_camera->screenToWorld(float(mx), float(my));
            m_camera->setTargetPosition(worldPos);
        }

        m_leftBtnDown = leftDown;

    }

    Application::~Application() {
        glfwTerminate();
        delete m_renderer;
        delete m_window;
        delete m_camera;
    }

}