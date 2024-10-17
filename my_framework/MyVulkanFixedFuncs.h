//
// Created by wangly on 2024/10/17.
// 固定功能

#pragma once

#include "core.h"
#include "MyVulkanSwapChain.h"
#include <vector>
#include <stdexcept>

class MyVulkanFixedFuncs {
public:
    MyVulkanFixedFuncs() = default;

    ~MyVulkanFixedFuncs() = default;

    //创建一个绘制三角形的功能
    void createTriangle(MyVulkanSwapChain myVulkanSwapChain, VkDevice device, VkPipelineLayout pipelineLayout);
};

