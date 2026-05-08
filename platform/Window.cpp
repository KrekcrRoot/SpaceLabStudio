//
// Created by /<R3/<(RR00T on 03.05.2026.
//

#include "Window.h"
//#include <iostream>

SpaceLab::Window::Window(int width, int height, const std::string &title) {

    if (!glfwInit()) {
        throw std::runtime_error("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if(window == nullptr){
        throw std::runtime_error("Failed to init WINDOW");
    }

    glfwMakeContextCurrent(window);

}

void *SpaceLab::Window::getNativeHandle() {
    return this->window;
}