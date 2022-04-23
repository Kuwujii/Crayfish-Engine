#pragma once

#include "ce_device.hpp"

#include <string>
#include <vector>

namespace ce {
    struct PipelineConfigInfo {

    };

    class CEpipeline {
        public:
        CEpipeline(CEdevice &device, const std::string &vertFilepath, const std::string &fragFilepath, const PipelineConfigInfo &configInfo);
        ~CEpipeline();

        CEpipeline(const CEpipeline&) = delete;
        void operator = (const CEpipeline&) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

        private:
        CEdevice &ceDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;

        static std::vector<char> readFile(const std::string &filePath);

        void createGraphicsPipeline(const std::string &vertFilepath, const std::string &fragFilepath, const PipelineConfigInfo &configInfo);
        void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);
    };
}