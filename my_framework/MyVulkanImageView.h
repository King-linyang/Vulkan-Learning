//
// Created by wangly on 2024/10/16.
// 图像视图

#pragma once

#include "MyVulkanSwapChain.h"
#include <vector>
#include "core.h"
#include <stdexcept>

class MyVulkanImageView {
public:
    MyVulkanImageView() = default;

    ~MyVulkanImageView() = default;

    //创建图像视图
    void createImageViews(MyVulkanSwapChain myVulkanSwapChain, VkDevice *device);

    //获取图像视图
    std::vector<VkImageView> getImageViews() { return swapChainImageViews; }

    //销毁图像视图
    void cleanUp(VkDevice *device) {
        //清理图像视图
        for (auto imageView: swapChainImageViews) {
            vkDestroyImageView(*device, imageView, nullptr);
        }
    }

    //获取图像视图
    std::vector<VkImageView> getSwapChainImageViews() {
        return swapChainImageViews;
    }

private:
    //存储图像视图
    std::vector<VkImageView> swapChainImageViews;
};
