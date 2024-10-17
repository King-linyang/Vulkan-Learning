//
// Created by wangly on 2024/10/17.
// 绘图

#pragma once

#include <vector>
#include "core.h"
#include "MyVulkanRenderPass.h"
#include "MyVulkanImageView.h"

class MyVulkanDraw {
public:
    MyVulkanDraw() = default;

    ~MyVulkanDraw() = default;

    //创建帧缓冲区
    void createFrameBuffers(MyVulkanImageView myVulkanImageView, MyVulkanRenderPass myVulkanRenderPass,
                            MyVulkanSwapChain myVulkanSwapChain, VkDevice device);

    //获取帧缓冲区
    std::vector<VkFramebuffer> getSwapChainFramebuffers() {
        return swapChainFramebuffers;
    }

private:
    //帧缓冲区
    std::vector<VkFramebuffer> swapChainFramebuffers;
};

