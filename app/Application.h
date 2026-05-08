//
// Created by /<R3/<(RR00T on 02.05.2026.
//

#ifndef SPACELABSTUDIO_APPLICATION_H
#define SPACELABSTUDIO_APPLICATION_H

#include <Renderer.h>
#include <Camera.h>
#include <Window.h>
#include <workspace/InfiniteGrid.h>

namespace SpaceLab {
    class Application {

    public:
        explicit Application();
        ~Application();

        void run();

    private:
        bool m_leftBtnDown = false;
        void handleInput();

        Camera      *m_camera;
        Renderer    *m_renderer;
        Window      *m_window;

        // workspace
        ui::InfiniteGrid m_infiniteGrid;

    };
}

#endif //SPACELABSTUDIO_APPLICATION_H
