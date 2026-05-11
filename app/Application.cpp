//
// Created by /<R3/<(RR00T on 02.05.2026.
//

#include "Application.h"
#include <backend/OpenGLRenderer.h>
#include <objects/NumberObject.h>
#include <GLFW/glfw3.h>

namespace SpaceLab {

    using clock = std::chrono::high_resolution_clock;

    Application::Application() {
        m_renderer = new render::OpenGLRenderer();
        m_camera = new render::Camera(1280, 720);

        m_window = new Window{1280, 720, "SpaceLab Studio"};
        m_renderer->init(m_window->getNativeHandle());

        m_objects.push_back(new ui::NumberObject({
            0, 0
        }, 100));

        m_objects.push_back(new ui::NumberObject({
            -200, 0
        }, 100));

        m_objects.push_back(new ui::NumberObject({
            200, 0
        }, 100));

    }

    void Application::run() {

        render::font::Font myFont;
        myFont.load("assets/fonts/Roboto-Regular.ttf", 24.0f);

        auto* handler = (GLFWwindow*) m_window->getNativeHandle();
        glfwSetScrollCallback(handler, scrollCallback);

        glfwSetWindowUserPointer(handler, this);

        GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CURSOR_NORMAL);
        GLFWcursor* crosshairCursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);

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

            glfwGetCursorPos(handler, &m_cursorPos.x, &m_cursorPos.y);
            auto worldPos = m_camera->screenToWorld(float(m_cursorPos.x), float(m_cursorPos.y));

            m_lastCursorPos = m_cursorPos;

            for(const auto object : m_objects) {

                object->update(float(dt));

                if(object->dragging() && m_dragging) {
                    object->drag(worldPos);
                }

                if(object->dragging() && !m_leftBtnDown) {
                    object->drop();
                    m_dragging = false;
                }

                if(object->hit(worldPos)) {
                    if(!m_dragging) {
                        glfwSetCursor(handler, crosshairCursor);
                        object->hover();
                    }

                    if(m_leftBtnDown && !m_dragging) {
                        object->drag(worldPos);
                        m_dragging = true;
                    }
                }else if(object->hovering()){
                    object->leave();
                    glfwSetCursor(handler, cursor);
                }
                object->draw(m_renderer);
            }

            m_renderer->drawString(myFont, "Hello, SpaceLab!", {10.f, 10.f});

            m_renderer->endFrame();

            glfwSwapBuffers(handler);
            glfwPollEvents();
        }


    }

    void Application::scrollCallback(GLFWwindow* window, double x, double y) {

        auto* app = reinterpret_cast<Application*> (glfwGetWindowUserPointer(window));
        app->m_camera->zoom((float) y);

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


        if(leftDown && m_leftBtnDown) {

        }

        m_leftBtnDown = leftDown;

    }

    Application::~Application() {
        glfwTerminate();
        delete m_renderer;
        delete m_window;
        delete m_camera;

        for(const auto& object : m_objects) {
            delete object;
        }
    }

}