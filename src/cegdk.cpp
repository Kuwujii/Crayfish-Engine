#pragma once

#include "cegdk.hpp"

#include <stdexcept>
#include <array>

namespace ce {
    CEGDK::CEGDK() {
        loadModels();
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    CEGDK::~CEGDK() {
        vkDestroyPipelineLayout(ceDevice.getDevice(), pipelineLayout, nullptr);
    }

    void CEGDK::run() {
        while(!ceWindow.shouldClose()) {
            glfwPollEvents();
            drawFrame();
        }

        vkDeviceWaitIdle(ceDevice.getDevice());
    }

    void CEGDK::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;

        if(vkCreatePipelineLayout(ceDevice.getDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }

    void CEGDK::createPipeline() {
        PipelineConfigInfo pipelineConfig = {};

        CEpipeline::defaultPipelineConfigInfo(pipelineConfig, ceSwapChain.getWidth(), ceSwapChain.getHeight());

        pipelineConfig.renderPass = ceSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        cePipeline = std::make_unique<CEpipeline>(ceDevice, "./build/Debug/shaders/simple.vert.spv", "./build/Debug/shaders/simple.frag.spv", pipelineConfig);
    }

    void CEGDK::createCommandBuffers() {
        commandBuffers.resize(ceSwapChain.getImageCount());

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = ceDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if(vkAllocateCommandBuffers(ceDevice.getDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffers");
        }

        for(int i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo = {};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("Failed to begin recording command buffer");
            }

            VkRenderPassBeginInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = ceSwapChain.getRenderPass();
            renderPassInfo.framebuffer = ceSwapChain.getFrameBuffer(i);
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = ceSwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues = {};
            clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            cePipeline->bind(commandBuffers[i]);
            ceModel->bind(commandBuffers[i]);
            ceModel->draw(commandBuffers[i]);

            vkCmdEndRenderPass(commandBuffers[i]);
            if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("Failed to record command buffer");
            }
        }
    }

    void CEGDK::drawFrame() {
        uint32_t imageIndex;
        auto result = ceSwapChain.acquireNextImage(&imageIndex);

        if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("Failed to acquire swap chain image");
        }

        result = ceSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

        if(result != VK_SUCCESS) {
            throw std::runtime_error("Failed to present swap chain image");
        }
    }

    void CEGDK::loadModels() {
        std::vector<CEmodel::Vertex> vertices {
            {{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
            {{0.5f, 0.5f}, {1.0f, 0.0f, 0.5f}},
            {{-0.5f, 0.5f}, {0.0f, 1.0f, 0.5f}}
        };

        ceModel = std::make_unique<CEmodel>(ceDevice, vertices);
    }
}