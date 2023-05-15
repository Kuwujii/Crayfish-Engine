#pragma once

#include "ce_window.hpp"

#include <string>
#include <vector>

namespace ce {
    struct QueueFamilyIndices {
        uint32_t graphicsFamily;
        uint32_t presentFamily;
        bool graphicsFamilyHasValue = false;
        bool presentFamilyHasValue = false;
        bool isComplete();
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class CEdevice {
        public:
        #ifdef NDEBUG
        const bool enableValidationLayers = false;
        #else
        const bool enableValidationLayers = true;
        #endif

        VkPhysicalDeviceProperties properties;

        CEdevice(CEwindow &window);
        ~CEdevice();

        CEdevice(const CEdevice&) = delete;
        CEdevice& operator = (const CEdevice&) = delete;
        CEdevice(CEdevice&&) = delete;
        CEdevice& operator = (CEdevice&&) = delete;

        VkDevice getDevice();
        SwapChainSupportDetails getSwapChainSupport();
        VkSurfaceKHR getSurface();
        VkCommandPool getCommandPool();
        VkQueue getGraphicsQueue();
        VkQueue getPresentQueue();

        QueueFamilyIndices findPhysicalQueueFamilies();
        VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
        
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

        private:
        const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
        const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        CEwindow &window;
        VkInstance instance;
        VkSurfaceKHR surface;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        VkCommandPool commandPool;

        void createInstance();
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createCommandPool();

        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        void hasGlfwRequiredInstanceExtensions();
        bool isDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    };
}