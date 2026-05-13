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

#include <ml/Recognizer.h>
#include <atomic>
#include <thread>
#include <string>
#include <vector>
#include <stdint.h>

namespace SpaceLab {
    class Application {

    public:
        explicit Application();
        ~Application();

        void run();

        void triggerRecognition();

        std::string lastLatexResult;
        
        std::atomic<bool> isRecognizing{false};

    private:
        bool m_leftBtnDown = false;
        bool m_dragging = false;
        void handleInput();
        static void scrollCallback(GLFWwindow* window, double x, double y);

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        Camera      *m_camera;
        Renderer    *m_renderer;
        Window      *m_window;

        std::vector<ui::Sprite*> m_objects;
        glm::vec<2, double> m_cursorPos;
        glm::vec<2, double> m_lastCursorPos;

        // workspace
        ui::InfiniteGrid m_infiniteGrid;

        Recognizer m_recognizer{"assets/models"};

        int m_windowWidth  = 1280;
        int m_windowHeight = 720;
    };
}

#endif //SPACELABSTUDIO_APPLICATION_H
