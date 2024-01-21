#pragma once

#include "ce_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace ce {
    class CEmodel {
        public:
        struct Vertex {
            glm::vec2 position;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        CEmodel(CEdevice &device, const std::vector<Vertex> &vertices);
        ~CEmodel();

        CEmodel(const CEmodel&) = delete;
        CEmodel& operator = (const CEmodel&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

        private:
        CEdevice &ceDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;

        void createVertexBuffers(const std::vector<Vertex> &vertices);
    };
}