#pragma once

#include "cegdk.hpp"

namespace ce {
    void CEGDK::run() {
        while(!ceWindow.shouldClose()) {
            glfwPollEvents();
        }
    }
}