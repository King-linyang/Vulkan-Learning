//
// Created by wangly on 2024/10/17.
//

#pragma once

#include "core.h"
#include <stdexcept>
#include "MyVulkanSwapChain.h"

class MyVulkanRenderPass {
public:
    MyVulkanRenderPass() = default;

    ~MyVulkanRenderPass() = default;

    //创建渲染过程
    void createRenderPass(MyVulkanSwapChain myVulkanSwapChain, VkDevice *device);

    //清理工作
    void cleanUp(VkDevice *device) {
        vkDestroyRenderPass(*device, renderPass, nullptr);
    }

    //获取渲染通道
    VkRenderPass getRenderPass() {
        return renderPass;
    }

    //清理帧缓冲
    void cleanUp(const std::vector<VkFramebuffer>& swapChainFramebuffers, VkDevice *device) {
        for (auto framebuffer: swapChainFramebuffers) {
            vkDestroyFramebuffer(*device, framebuffer, nullptr);
        }
    }

private:
    //渲染通道
    VkRenderPass renderPass;
};

