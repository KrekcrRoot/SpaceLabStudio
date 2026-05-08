//
// Created by /<R3/<(RR00T on 02.05.2026.
//

#ifndef SPACELABSTUDIO_APPLICATION_H
#define SPACELABSTUDIO_APPLICATION_H

#include <Renderer.h>

#include <Window.h>

namespace SpaceLab {
    class Application {

    public:
        explicit Application();
        ~Application();

        void run();

    private:

        Renderer *renderer;
        Window *window;

    };
}

#endif //SPACELABSTUDIO_APPLICATION_H
