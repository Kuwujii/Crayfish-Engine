#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace ce {
    class CEwindow {
        public:
        CEwindow(int w, int h, std::string name);
        ~CEwindow();

        CEwindow(const CEwindow&) = delete;
        CEwindow &operator = (const CEwindow&) = delete;

        bool shouldClose() { 
            return glfwWindowShouldClose(window);
        }

        private:

        void initWindow();

        const int width;
        const int height;

        std::string windowName;

        GLFWwindow *window;
    };
}