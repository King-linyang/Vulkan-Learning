//
// Created by wangly on 2024/10/17.
//

#pragma once

#include "core.h"
#include <stdexcept>
#include "MyVulkanSwapChain.h"
#include "MyVulkanSwapChain.h"

class MyVulkanRenderPass {
public:
    //创建渲染过程
    void createRenderPass(MyVulkanSwapChain myVulkanSwapChain, VkDevice device);

    //清理工作
    void cleanUp(VkDevice device) {
        vkDestroyRenderPass(device, renderPass, nullptr);
    }

private:
    //渲染通道
    VkRenderPass renderPass;
};

