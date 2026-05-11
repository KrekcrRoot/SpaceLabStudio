//
// Created by /<R3/<(RR00T on 02.05.2026.
//

#ifndef SPACELABSTUDIO_APPLICATION_H
#define SPACELABSTUDIO_APPLICATION_H

#include <Renderer.h>
#include <Camera.h>
#include <Window.h>
#include <workspace/InfiniteGrid.h>
#include <Sprite.h>

namespace SpaceLab {
    class Application {

    public:
        explicit Application();
        ~Application();

        void run();

    private:
        bool m_leftBtnDown = false;
        bool m_dragging = false;
        void handleInput();
        static void scrollCallback(GLFWwindow* window, double x, double y);

        Camera      *m_camera;
        Renderer    *m_renderer;
        Window      *m_window;

        std::vector<ui::Sprite*> m_objects;
        glm::vec<2, double> m_cursorPos;
        glm::vec<2, double> m_lastCursorPos;

        // workspace
        ui::InfiniteGrid m_infiniteGrid;

    };
}

#endif //SPACELABSTUDIO_APPLICATION_H
