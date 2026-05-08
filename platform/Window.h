//
// Created by /<R3/<(RR00T on 03.05.2026.
//

#ifndef SPACELABSTUDIO_WINDOW_H
#define SPACELABSTUDIO_WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SpaceLab {

    class Window {

    public:
        Window(int width, int height, const std::string& title);
        void* getNativeHandle();

    private:
        GLFWwindow *window;

    };

}



#endif //SPACELABSTUDIO_WINDOW_H
