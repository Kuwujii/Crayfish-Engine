#pragma once

#include "cegdk.hpp"

namespace ce {
    void CEGDK::run() {
        while(!CEwindow.shouldClose()) {
            glfwPollEvents();
        }
    }
}