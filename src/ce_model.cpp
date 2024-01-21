#include "ce_model.hpp"

namespace ce {
    std::vector<VkVertexInputBindingDescription> CEmodel::Vertex::getBindingDescriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> CEmodel::Vertex::getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(1);
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = 0;
        return attributeDescriptions;
    }

    CEmodel::CEmodel(CEdevice &device, const std::vector<Vertex> &vertices) : ceDevice{device} {
        createVertexBuffers(vertices);
    }

    CEmodel::~CEmodel() {
        vkDestroyBuffer(ceDevice.getDevice(), vertexBuffer, nullptr);
        vkFreeMemory(ceDevice.getDevice(), vertexBufferMemory, nullptr);
    }

    void CEmodel::bind(VkCommandBuffer commandBuffer) {
        VkBuffer buffers[] = {vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
    }

    void CEmodel::draw(VkCommandBuffer commandBuffer) {
        vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
    }

    void CEmodel::createVertexBuffers(const std::vector<Vertex> &vertices) {
        vertexCount = static_cast<uint32_t>(vertices.size());
        assert(vertexCount >= 3 && "Vertex count must be at least 3.");
        VkDeviceSize bufferSize = sizeof(vertices[0])*vertexCount;
        ceDevice.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer, vertexBufferMemory);

        void *data;
        vkMapMemory(ceDevice.getDevice(), vertexBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
        vkUnmapMemory(ceDevice.getDevice(), vertexBufferMemory);
    }
}