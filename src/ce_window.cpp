#include "ce_window.hpp"

#include <string>

namespace ce {
    CEwindow::CEwindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
        initWindow();
    }

    CEwindow::~CEwindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void CEwindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }
}