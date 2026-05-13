//
// Created by /<R3/<(RR00T on 02.05.2026.
//

#ifndef SPACELABSTUDIO_APPLICATION_H
#define SPACELABSTUDIO_APPLICATION_H

//#include <glad/glad.h>
#include <Renderer.h>
#include <Camera.h>
#include <Window.h>
#include <widgets/widgets.h>
#include <workspace/InfiniteGrid.h>
#include <objects/Object.h>
#include <map>

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

        void loadFonts();

        std::map<std::string, render::font::Font*> m_fonts;

        render::Camera      *m_camera;
        render::Renderer    *m_renderer;
        Window      *m_window;


        ui::WidgetManager* m_widgetManager;
        std::vector<ui::Object*> m_objects;
        glm::vec<2, double> m_cursorPos {};
        glm::vec<2, double> m_lastCursorPos {};

        // workspace
        ui::InfiniteGrid m_infiniteGrid;

    };
}

#endif //SPACELABSTUDIO_APPLICATION_H
