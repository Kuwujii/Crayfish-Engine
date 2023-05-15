#pragma once

#include "ce_device.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace ce {
    class CEswapchain {
        public:
        static constexpr int MAX_FRAMES_IN_FLIGHT = 3;

        CEswapchain(CEdevice &deviceRef, VkExtent2D windowExtent);
        ~CEswapchain();

        CEswapchain(const CEswapchain&) = delete;
        CEswapchain& operator = (const CEswapchain&) = delete;

        uint32_t getWidth();
        uint32_t getHeight();
        VkRenderPass getRenderPass();
        VkFormat getSwapChainImageFormat();
        size_t getImageCount();
        VkFramebuffer getFrameBuffer(int index);
        VkExtent2D getSwapChainExtent();
        VkImageView getImageView(int index);
        float getExtentAspectRatio();

        VkFormat findDepthFormat();
        VkResult acquireNextImage(uint32_t *imageIndex);
        VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

        private:
        CEdevice &device;
        VkExtent2D windowExtent;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        VkRenderPass renderPass;
        std::vector<VkImage> depthImages;
        std::vector<VkDeviceMemory> depthImageMemorys;
        std::vector<VkImageView> depthImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;

        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createDepthResources();
        void createFramebuffers();
        void createSyncObjects();

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
    };
}