//
// Created by wangly on 2024/10/17.
// 图形渲染管线

#include <vector>
#include <stdexcept>
#include <iostream>

#include "MyVulkanGraphicsPipeline.h"
#include "MyVulkanFixedFuncs.h"

void MyVulkanGraphicsPipeline::createGraphicsPipeline(MyVulkanShaderCompile myVulkanShaderCompile, VkDevice device,
                                                      MyVulkanSwapChain myVulkanSwapChain,
                                                      MyVulkanFixedFuncs myVulkanFixedFuncs) {
    // 加载着色器字节码
    std::vector<char> vertShaderCode = myVulkanShaderCompile.loadShader("vertex.vert");
    std::vector<char> fragShaderCode = myVulkanShaderCompile.loadShader("fragment.frag");

    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode, device);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, device);

    //通过 VkPipelineShaderStageCreateInfo 结构将它们分配到特定的管道阶段。以使用着色器
    //告诉 Vulkan 将在哪个管道阶段使用着色器
    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;

    vertShaderStageInfo.module = vertShaderModule;
    //指定调用的函数
    vertShaderStageInfo.pName = "main";

    //创建片段着色器
    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";
    //定义一个包含这两个结构的数组，使用它来在实际的管道创建步骤中引用它们
    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    //固定功能
    myVulkanFixedFuncs.createTriangle(myVulkanSwapChain, device, pipelineLayout);


    //管道创建完成，销毁着色器模块
    vkDestroyShaderModule(device, fragShaderModule, nullptr);
    vkDestroyShaderModule(device, vertShaderModule, nullptr);
}

VkShaderModule MyVulkanGraphicsPipeline::createShaderModule(const std::vector<char> &code, VkDevice device) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());
    //创建 vkCreateShaderModule
    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }
    return shaderModule;
}
