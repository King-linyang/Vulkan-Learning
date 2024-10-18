//
// Created by wangly on 2024/10/17.
// 图形渲染管线

#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include "MyVulkanShaderCompile.h"
#include "MyVulkanSwapChain.h"
#include "MyVulkanFixedFuncs.h"

class MyVulkanGraphicsPipeline {
public:
    MyVulkanGraphicsPipeline() = default;

    ~MyVulkanGraphicsPipeline() = default;

    //创建一个图形管线
    void createGraphicsPipeline(MyVulkanShaderCompile myVulkanShaderCompile, VkDevice *device,
                                MyVulkanSwapChain &myVulkanSwapChain, MyVulkanFixedFuncs myVulkanFixedFuncs,
                                VkRenderPass renderPass, VkPipeline pT);

    //创建着色器模块 采用一个以字节码为参数的缓冲区，并从中创建一个 VkShaderModule
    VkShaderModule createShaderModule(const std::vector<char> &code, VkDevice device);

    //销毁管道
    void cleanUp(VkDevice *device) {
        vkDestroyPipelineLayout(*device, pipelineLayout, nullptr);
    }

    //获取图形管线
    VkPipeline getGraphicsPipeline() {
        return graphicsPipeline;
    }

    //获取管线布局
    VkPipelineLayout getPipelineLayout() {
        return pipelineLayout;
    }

private:
    //管线布局
    VkPipelineLayout pipelineLayout;
    //图形管线
    VkPipeline graphicsPipeline;
};


