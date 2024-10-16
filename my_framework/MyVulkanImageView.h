//
// Created by wangly on 2024/10/16.
// 图像视图

#pragma once

#include <vector>
#include "core.h"

class MyVulkanImageView {
public:
    MyVulkanImageView() = default;

    ~MyVulkanImageView() = default;

    //创建图像视图
    void createImageViews();

public:
    //存储图像视图
    std::vector<VkImageView> swapChainImageViews;
};
