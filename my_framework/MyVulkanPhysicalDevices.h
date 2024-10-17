//
// Created by wangly on 2024/10/16.
// 物理设备

#pragma once

#include "MyVulkanSwapChain.h"
#include <optional>
#include <stdexcept>
#include <vector>
#include <set>
#include "core.h"

struct QueueFamilyIndices {
    //图形队列家族索引
    std::optional<uint32_t> graphicsFamily;
    //呈现队列家族索引
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class MyVulkanPhysicalDevices {
public:
    MyVulkanPhysicalDevices() = default;

    ~MyVulkanPhysicalDevices() = default;

    //选择物理设备 显卡等
    static void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice *physicalDevice, VkSurfaceKHR surface);

    //寻找一个支持 graphics 命令的队列
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
    //检查设备是否支持
    static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

private:
    static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
};

