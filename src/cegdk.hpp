#pragma once

#include "ce_window.hpp"
#include "ce_pipeline.hpp"
#include "ce_swap_chain.hpp"
#include "ce_device.hpp"

#include <memory>
#include <vector>

namespace ce {
    class CEGDK {
        public:
        static constexpr int WIDTH = 1280;
        static constexpr int HEIGHT = 720;

        CEGDK();
        ~CEGDK();

        CEGDK(const CEGDK&) = delete;
        CEGDK& operator = (const CEGDK&) = delete;

        void run();

        private:
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

        CEwindow ceWindow = {WIDTH, HEIGHT, "Crayfish Engine"};
        CEdevice ceDevice = {ceWindow};
        CEswapchain ceSwapChain = {ceDevice, ceWindow.getExtent()};
        std::unique_ptr<CEpipeline> cePipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
    };
}