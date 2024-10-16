//
// Created by wangly on 2024/10/16.
// 图像视图

#pragma once

#include <vector>
#include "core.h"
#include "MyVulkanSwapChain.h"

class MyVulkanImageView {
public:
    MyVulkanImageView() = default;

    ~MyVulkanImageView() = default;

    //创建图像视图
    void createImageViews(MyVulkanSwapChain myVulkanSwapChain, VkDevice device);

    //获取图像视图
    std::vector<VkImageView> getImageViews() { return swapChainImageViews; }

    //销毁图像视图
    void cleanUp(VkDevice device);

private:
    //存储图像视图
    std::vector<VkImageView> swapChainImageViews;
};
