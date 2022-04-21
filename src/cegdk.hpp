#pragma once

#include "ce_window.hpp"

namespace ce {
    class CEGDK {
        public:
        static constexpr int WIDTH = 1280;
        static constexpr int HEIGHT = 720;

        void run();

        private:
        CEwindow CEwindow{WIDTH, HEIGHT, "Crayfish Engine GDK"};  
    };
}