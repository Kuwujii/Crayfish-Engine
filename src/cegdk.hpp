#pragma once

#include "ce_window.hpp"
#include "ce_pipeline.hpp"
#include "ce_device.hpp"

namespace ce {
    class CEGDK {
        public:
        static constexpr int WIDTH = 1280;
        static constexpr int HEIGHT = 720;

        void run();

        private:
        CEwindow ceWindow{WIDTH, HEIGHT, "Crayfish Engine"};
        CEdevice ceDevice{ceWindow};
        CEpipeline cePipeline{ceDevice, "build/Debug/shaders/simple.vert.spv", "build/Debug/shaders/simple.frag.spv", CEpipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
    };
}