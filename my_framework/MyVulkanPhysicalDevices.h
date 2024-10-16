//
// Created by wangly on 2024/10/16.
// 物理设备

#pragma once

#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

class MyVulkanPhysicalDevices {
public:
    MyVulkanPhysicalDevices() = default;

    ~MyVulkanPhysicalDevices() = default;

    //选择物理设备 显卡等
    static void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice *physicalDevice);

    //寻找一个支持 graphics 命令的队列
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

private:
    static bool isDeviceSuitable(VkPhysicalDevice device);
};

