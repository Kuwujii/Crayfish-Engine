#include "ce_window.hpp"

#include <string>
#include <stdexcept>

namespace ce {
    CEwindow::CEwindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
        initWindow();
    }

    CEwindow::~CEwindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    VkExtent2D CEwindow::getExtent() {
        return {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };
    }

    bool CEwindow::shouldClose() { 
        return glfwWindowShouldClose(window);
    }

    void CEwindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface");
        }
    }

    void CEwindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }
}