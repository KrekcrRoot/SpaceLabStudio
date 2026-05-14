//
// Created by /<R3/<(RR00T on 02.05.2026.
//

#include "Application.h"
#include <GLFW/glfw3.h>
#include <backend/OpenGLRenderer.h>
#include <objects/objects.h>


namespace SpaceLab {

    using clock = std::chrono::high_resolution_clock;

    Application::Application() {

        m_renderer = new render::OpenGLRenderer();
        m_camera = new render::Camera(1280, 720);

        m_window = new Window{1280, 720, "SpaceLab Studio"};
        m_renderer->init(m_window->getNativeHandle());

        loadFonts();

        m_interface = new ui::Interface(m_fontManager);

        m_objects.push_back(new ui::NumberObject({
            0, 0
        }, 100));

    }

    void Application::loadFonts() {
        m_fontManager = new ui::FontManager();

        auto* defaultFont = new render::font::Font();
        defaultFont->load("assets/fonts/Roboto-Regular.ttf", 24.f);

        m_fontManager->addFont("default", defaultFont);

        auto* mathFont = new render::font::Font();
        mathFont->load("assets/fonts/NotoSansMath-Regular.ttf", 24.f);

        m_fontManager->addFont("math", mathFont);
    }

    void Application::run() {


        auto* handler = (GLFWwindow*) m_window->getNativeHandle();
        glfwSetScrollCallback(handler, scrollCallback);

        glfwSetWindowUserPointer(handler, this);

        GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CURSOR_NORMAL);

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
                        glfwSetCursor(handler, object->cursor());
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
            

            m_renderer->endFrame();

            m_renderer->beginUI();
            m_interface->draw(m_renderer);
            m_renderer->endUI();

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

        if(leftDown && !m_leftBtnDown && !m_dragging) {
            auto pos = m_camera->screenToWorld(float(m_cursorPos.x), float(m_cursorPos.y));;
        }

        if(leftDown && m_leftBtnDown) {

        }

        m_leftBtnDown = leftDown;

    }

    Application::~Application() {
        glfwTerminate();
        delete m_renderer;
        delete m_window;
        delete m_camera;
        delete m_interface;
        delete m_fontManager;

        for(const auto& object : m_objects) {
            delete object;
        }
    }

}