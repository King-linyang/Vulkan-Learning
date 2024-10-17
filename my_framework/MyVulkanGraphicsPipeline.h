//
// Created by wangly on 2024/10/17.
// 图形渲染管线

#pragma once

#include "MyVulkanShaderCompile.h"

class MyVulkanGraphicsPipeline {
public:
    MyVulkanGraphicsPipeline() = default;

    ~MyVulkanGraphicsPipeline() = default;

    //创建一个图形管线
    void createGraphicsPipeline(MyVulkanShaderCompile myVulkanShaderCompile, VkDevice device);

    //创建着色器模块 采用一个以字节码为参数的缓冲区，并从中创建一个 VkShaderModule
    VkShaderModule createShaderModule(const std::vector<char> &code, VkDevice device);
};


