//
// Created by wangly on 2024/10/17.
// 固定功能

#pragma once
#include "core.h"

class MyVulkanFixedFuncs {
public:
    MyVulkanFixedFuncs() = default;

    ~MyVulkanFixedFuncs() = default;

    //创建一个绘制三角形的功能
    void createTriangle(VkExtent2D swapChainExtent, VkDevice device, VkPipelineLayout pipelineLayout,
                        VkPipelineShaderStageCreateInfo shaderStages[], VkRenderPass renderPass,
                        VkPipeline *graphicsPipeline);

    //创建三角形，使用顶点缓冲区
    void createTriangle1(VkExtent2D swapChainExtent, VkDevice device, VkPipelineLayout *pipelineLayout,
                         VkPipelineShaderStageCreateInfo shaderStages[], VkRenderPass renderPass,
                         VkPipeline *graphicsPipeline, VkDescriptorSetLayout *descriptorSetLayout);
};

