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

        bool shouldClose();
        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

        private:
        const int width;
        const int height;

        std::string windowName;
        GLFWwindow *window;

        void initWindow();
    };
}